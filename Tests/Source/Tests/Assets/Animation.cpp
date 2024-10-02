#include "Assets/Animation.h"

#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(Animation, Create)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Animation> animation = Animation::Create();
		EXPECT_NE(animation, nullptr);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animation, Frames)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Animation> animation = Animation::Create();
		EXPECT_EQ(animation->GetFrameCount(), 0);

		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		texture->CreateSliceGrid({4, 4});

		const SharedPtr<AnimationFrame> frame1 = animation->AddFrame(texture->GetSlice(0), 0.1f);
		EXPECT_NE(frame1, nullptr);
		EXPECT_EQ(animation->GetFrameCount(), 1);

		const SharedPtr<AnimationFrame> frame2 = animation->AddFrame(texture->GetSlice(1), 0.2f);
		EXPECT_NE(frame2, nullptr);
		EXPECT_EQ(animation->GetFrameCount(), 2);

		EXPECT_THROW(animation->AddFrame(nullptr, 0.3f), std::invalid_argument);

		EXPECT_THROW(animation->AddFrame(texture->GetSlice(2), 0.0f), std::invalid_argument);
		EXPECT_THROW(animation->AddFrame(texture->GetSlice(2), -0.1f), std::invalid_argument);

		EXPECT_THROW(animation->AddFrame(texture->GetSlice(2), 0.5f, 3), std::invalid_argument);

		EXPECT_EQ(animation->GetFrameCount(), 2);

		EXPECT_THROW(animation->GetFrame(3), std::invalid_argument);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Animation, Duration)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Animation> animation = Animation::Create();
		EXPECT_EQ(animation->GetFrameCount(), 0);

		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		texture->CreateSliceGrid({4, 4});

		const SharedPtr<AnimationFrame> frame1 = animation->AddFrame(texture->GetSlice(0), 0.1f);
		EXPECT_NEAR(animation->GetDuration(), 0.1f, 0.001f);
		EXPECT_TRUE(animation->IsUsingDefaultDuration());

		const SharedPtr<AnimationFrame> frame2 = animation->AddFrame(texture->GetSlice(1), 0.2f);
		EXPECT_NEAR(animation->GetDuration(), 0.3f, 0.001f);
		EXPECT_NEAR(animation->GetDefaultDuration(), 0.3f, 0.001f);
		EXPECT_TRUE(animation->IsUsingDefaultDuration());

		animation->SetDuration(2.5f);
		EXPECT_NEAR(animation->GetDuration(), 2.5f, 0.001f);
		EXPECT_NEAR(animation->GetDefaultDuration(), 0.3f, 0.001f);
		EXPECT_FALSE(animation->IsUsingDefaultDuration());

		const SharedPtr<AnimationFrame> frame3 = animation->AddFrame(texture->GetSlice(2), 0.3f);
		EXPECT_NEAR(animation->GetDuration(), 2.5f, 0.001f);
		EXPECT_NEAR(animation->GetDefaultDuration(), 0.6f, 0.001f);
		EXPECT_FALSE(animation->IsUsingDefaultDuration());

		animation->UseDefaultDuration();
		EXPECT_NEAR(animation->GetDuration(), 0.6f, 0.001f);
		EXPECT_NEAR(animation->GetDefaultDuration(), 0.6f, 0.001f);
		EXPECT_TRUE(animation->IsUsingDefaultDuration());

		EndTest();
	}
}
END_GAME_TEST()
