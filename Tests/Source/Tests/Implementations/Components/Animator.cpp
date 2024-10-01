﻿#include "Implementations/Components/Animator.h"

#include "Assets/Animation.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Helper classes

namespace
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false)
		{}
	};
}

// Mock Services

namespace
{
	class MockClock final : public Clock
	{
		std::chrono::steady_clock::time_point CalculateCurrentTime() const override
		{
			return m_LastFrameTime + std::chrono::milliseconds(150);
		}
	};

	SharedPtr<Animation> CreateAnimation()
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		texture->CreateSliceGrid({4, 4});

		SharedPtr<Animation> animation = Animation::Create();
		animation->AddFrame(texture->GetSlice(0), 0.1f);
		animation->AddFrame(texture->GetSlice(1), 0.1f);
		animation->AddFrame(texture->GetSlice(2), 0.2f);
		animation->AddFrame(texture->GetSlice(3), 0.3f);

		return animation;
	}

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockClock>();
	}
}

// Tests

BEGIN_GAME_TEST(Animator, Animation)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		const SharedPtr<Animation> animation = CreateAnimation();

		EXPECT_EQ(animator->GetAnimation(), nullptr);

		animator->SetAnimation(animation);
		EXPECT_EQ(animator->GetAnimation(), animation);

		animator->SetAnimation(nullptr);
		EXPECT_EQ(animator->GetAnimation(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animator, TargetUniform)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
		SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();

		EXPECT_EQ(animator->GetTargetUniform(), nullptr);

		animator->SetTargetUniform(material->Sprite);
		EXPECT_EQ(animator->GetTargetUniform(), material->Sprite);

		animator->SetTargetUniform(nullptr);
		EXPECT_EQ(animator->GetTargetUniform(), nullptr);

		Animator* otherAnimator = entity->AttachComponent<Animator>();
		otherAnimator->SetTargetUniform(material->Sprite);
		EXPECT_THROW(animator->SetTargetUniform(material->Sprite), std::invalid_argument);

		otherAnimator->Detach();
		animator->SetTargetUniform(material->Sprite);
		EXPECT_EQ(animator->GetTargetUniform(), material->Sprite);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animator, Loop)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();

		EXPECT_EQ(animator->GetLoop(), false);

		animator->SetLoop(true);
		EXPECT_EQ(animator->GetLoop(), true);

		animator->SetLoop(false);
		EXPECT_EQ(animator->GetLoop(), false);

		EndTest();
	}
}
END_GAME_TEST()


BEGIN_GAME_TEST(Animator, PlaybackControls)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();

		SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();
		const SharedPtr<Animation> animation = CreateAnimation();

		animator->Play();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);

		animator->Pause();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);

		animator->Play();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);

		animator->Stop();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);

		animator->SetAnimation(animation);
		animator->SetTargetUniform(material->Sprite);

		animator->Play();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Playing);

		animator->Pause();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Paused);

		animator->Play();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Playing);

		animator->Stop();
		ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Animator, PlaybackCompletion, MockServiceBuilder)
{
	i32 GetOrderOfExecution() const override
	{
		// TODO remove this and set the animator order to -1
		return 1;
	}

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		static Animator* animator = nullptr;
		static SharedPtr<DefaultSpriteMaterial> material = nullptr;
		static SharedPtr<Animation> animation = nullptr;

		if (frame == 1)
		{
			TestEntity* entity = SpawnEntity<TestEntity>();
			animator = entity->AttachComponent<Animator>();

			SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
			material = spriteRenderer->UseDefaultMaterial();
			animation = CreateAnimation();

			animator->SetAnimation(animation);
			animator->SetTargetUniform(material->Sprite);
			animator->Play();
		}

		if (frame == 1)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), 0.0f, 0.001f);
			EXPECT_EQ(material->Sprite->Value, nullptr);
		}

		if (frame == 2)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), 0.15f, 0.001f);
			EXPECT_EQ(material->Sprite->Value, animation->GetFrame(1)->GetSprite());
		}

		if (frame == 3)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), 0.30f, 0.001f);
			EXPECT_EQ(material->Sprite->Value, animation->GetFrame(2)->GetSprite());
		}

		if (frame == 4)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), 0.45f, 0.001f);
			EXPECT_EQ(material->Sprite->Value, animation->GetFrame(3)->GetSprite());
		}

		if (frame == 5)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), 0.60f, 0.001f);
			EXPECT_EQ(material->Sprite->Value, animation->GetFrame(3)->GetSprite());
		}

		if (frame == 6)
		{
			ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Stopped);
			ASSERT_NEAR(animator->GetTime(), 0.0f, 0.001f);

			material = nullptr;
			animation = nullptr;
			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Animator, PlaybackWithLoop, MockServiceBuilder)
{
	i32 GetOrderOfExecution() const override
	{
		// TODO remove this and set the animator order to -1
		return 1;
	}

	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		static Animator* animator = nullptr;

		if (frame == 1)
		{
			TestEntity* entity = SpawnEntity<TestEntity>();
			animator = entity->AttachComponent<Animator>();

			SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
			SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();
			const SharedPtr<Animation> animation = CreateAnimation();

			animator->SetAnimation(animation);
			animator->SetTargetUniform(material->Sprite);
			animator->SetLoop(true);
			animator->Play();
		}

		if (frame >= 1 && frame <= 5)
		{
			EXPECT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), (frame - 1) * 0.15f, 0.001f);
		}

		if (frame == 6)
		{
			ASSERT_EQ(animator->GetStatus(), AnimatorStatus::Playing);
			EXPECT_NEAR(animator->GetTime(), (frame - 1) * 0.15f - animator->GetAnimation()->GetDuration(), 0.001f);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animator, JumpToTime)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();

		animator->JumpToTime(0.5f);
		EXPECT_EQ(animator->GetTime(), 0.0f);

		const SharedPtr<Animation> animation = CreateAnimation();
		animator->SetAnimation(animation);

		animator->JumpToTime(0.5f);
		EXPECT_EQ(animator->GetTime(), 0.5f);

		EXPECT_THROW(animator->JumpToTime(-0.5f), std::invalid_argument);
		EXPECT_THROW(animator->JumpToTime(1.5f), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animator, ApplyCurrentFrame)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();

		SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();
		const SharedPtr<Animation> animation = CreateAnimation();

		animator->SetAnimation(animation);
		animator->SetTargetUniform(material->Sprite);

		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(0)->GetSprite());

		animator->JumpToTime(0.05f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(0)->GetSprite());

		animator->JumpToTime(0.15f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(1)->GetSprite());

		animator->JumpToTime(0.25f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(2)->GetSprite());

		animator->JumpToTime(0.45f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(3)->GetSprite());

		animator->JumpToTime(0.05f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(material->Sprite->Value, animation->GetFrame(0)->GetSprite());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animator, OnTargetUniformDeleted)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		SpriteRenderer* spriteRenderer = entity->AttachComponent<SpriteRenderer>();
		SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();

		animator->SetTargetUniform(material->Sprite);
		ASSERT_EQ(animator->GetTargetUniform(), material->Sprite);

		spriteRenderer->SetMaterial(nullptr);
		material = nullptr;

		ASSERT_EQ(animator->GetTargetUniform(), nullptr);

		EndTest();
	}
}
END_GAME_TEST()
