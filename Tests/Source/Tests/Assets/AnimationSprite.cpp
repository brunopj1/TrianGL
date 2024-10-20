#include "Assets/AnimationSprite.h"

#include "Assets/Animation.h"
#include "Rendering/Animator.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Helper classes

namespace
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};
}

// Helper methods

namespace
{
	SharedPtr<Animation> CreateAnimation()
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		SharedPtr<Animation> animation = Animation::Create();

		const SharedPtr<TextureSlice> slice1 = texture->CreateAndGetSlice({4, 4}, {0, 0});
		animation->AddFrame(slice1, 1.0f);

		const SharedPtr<TextureSlice> slice2 = texture->CreateAndGetSlice({4, 8}, {0, 0});
		animation->AddFrame(slice2, 1.0f);

		const SharedPtr<TextureSlice> slice3 = texture->CreateAndGetSlice({4, 2}, {0, 0});
		animation->AddFrame(slice3, 1.0f);

		return animation;
	}
}

// Tests

BEGIN_GAME_TEST(AnimationSprite, GetCurrentSprite)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		const SharedPtr<Animation> animation = CreateAnimation();

		animator->SetAnimation(animation);
		SharedPtr<AnimationSprite> sprite = animator->GetAnimationSprite();
		EXPECT_EQ(sprite->GetCurrentSprite(), nullptr);

		animator->JumpToTime(0.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetCurrentSprite(), animation->GetFrame(0)->GetSprite());

		animator->JumpToTime(1.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetCurrentSprite(), animation->GetFrame(1)->GetSprite());

		animator->JumpToTime(2.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetCurrentSprite(), animation->GetFrame(2)->GetSprite());

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(AnimationSprite, GetResolution)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		const SharedPtr<Animation> animation = CreateAnimation();

		animator->SetAnimation(animation);
		SharedPtr<AnimationSprite> sprite = animator->GetAnimationSprite();

		animator->JumpToTime(0.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetResolution().x, 4);
		EXPECT_EQ(sprite->GetResolution().y, 4);

		animator->JumpToTime(1.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetResolution().x, 4);
		EXPECT_EQ(sprite->GetResolution().y, 8);

		animator->JumpToTime(2.5f);
		animator->ApplyCurrentFrame();
		EXPECT_EQ(sprite->GetResolution().x, 4);
		EXPECT_EQ(sprite->GetResolution().y, 2);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(AnimationSprite, GetAspectRatio)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		Animator* animator = entity->AttachComponent<Animator>();
		const SharedPtr<Animation> animation = CreateAnimation();

		animator->SetAnimation(animation);
		SharedPtr<AnimationSprite> animationSprite = animator->GetAnimationSprite();

		animator->JumpToTime(0.5f);
		animator->ApplyCurrentFrame();
		EXPECT_NEAR(animationSprite->GetCurrentSprite()->GetAspectRatio(), 1.0f, 0.001f);

		animator->JumpToTime(1.5f);
		animator->ApplyCurrentFrame();
		EXPECT_NEAR(animationSprite->GetCurrentSprite()->GetAspectRatio(), 0.5f, 0.001f);

		animator->JumpToTime(2.5f);
		animator->ApplyCurrentFrame();
		EXPECT_NEAR(animationSprite->GetCurrentSprite()->GetAspectRatio(), 2.0f, 0.001f);

		EndTest();
	}
}
END_GAME_TEST()
