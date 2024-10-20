#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(TextureSlice, CreateSlice)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);
		EXPECT_EQ(texture->GetSliceCount(), 0);

		const u32 sliceIdx1 = texture->CreateSlice({4, 4}, {0, 0});
		const SharedPtr<TextureSlice> slice1 = texture->GetSlice(sliceIdx1);
		EXPECT_EQ(sliceIdx1, 0);
		EXPECT_EQ(texture->GetSliceCount(), 1);
		EXPECT_NE(slice1.Get(), nullptr);

		const SharedPtr<TextureSlice> slice2 = texture->CreateAndGetSlice({4, 4}, {4, 0});
		EXPECT_EQ(texture->GetSliceCount(), 2);
		EXPECT_NE(slice2.Get(), nullptr);

		EXPECT_THROW(texture->CreateSlice({0, 4}, {4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSlice({-4, 4}, {4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSlice({44, 4}, {4, 4}), std::invalid_argument);

		EXPECT_THROW(texture->CreateSlice({4, 4}, {-4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSlice({4, 4}, {44, 4}), std::invalid_argument);

		EXPECT_THROW(texture->CreateSlice({4, 4}, {14, 4}), std::invalid_argument);

		EXPECT_EQ(texture->GetSliceCount(), 2);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(TextureSlice, CreateSliceGrid)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		const u32 sliceCount1 = texture->CreateSliceGrid({4, 4});
		EXPECT_EQ(sliceCount1, 16);
		EXPECT_EQ(texture->GetSliceCount(), 16);

		for (u32 i = 0; i < sliceCount1; i++)
		{
			const SharedPtr<TextureSlice> slice = texture->GetSlice(i);
			EXPECT_NE(slice.Get(), nullptr);
		}

		const std::vector<SharedPtr<TextureSlice>> slices = texture->CreateAndGetSliceGrid({4, 4}, {1, 1}, {1, 1});
		EXPECT_EQ(slices.size(), 9);
		EXPECT_EQ(texture->GetSliceCount(), 25);

		for (SharedPtr<TextureSlice> slice : slices)
		{
			EXPECT_NE(slice.Get(), nullptr);
		}

		EXPECT_THROW(texture->CreateSliceGrid({0, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSliceGrid({-4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSliceGrid({44, 4}), std::invalid_argument);

		EXPECT_THROW(texture->CreateSliceGrid({4, 4}, {-4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSliceGrid({4, 4}, {44, 4}), std::invalid_argument);

		EXPECT_THROW(texture->CreateSliceGrid({4, 4}, {4, 4}, {-4, 4}), std::invalid_argument);
		EXPECT_THROW(texture->CreateSliceGrid({4, 4}, {4, 4}, {44, 4}), std::invalid_argument);

		EXPECT_THROW(texture->CreateSliceGrid({10, 10}, {8, 8}, {4, 4}), std::invalid_argument);

		EXPECT_EQ(texture->GetSliceCount(), 25);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(TextureSlice, GetTexture)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		const SharedPtr<TextureSlice> slice = texture->CreateAndGetSlice({4, 4}, {0, 0});
		EXPECT_NE(slice.Get(), nullptr);

		EXPECT_EQ(slice->GetTexture(), texture);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(TextureSlice, GetResolution)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		const SharedPtr<TextureSlice> slice = texture->CreateAndGetSlice({4, 4}, {0, 0});
		EXPECT_NE(slice.Get(), nullptr);

		EXPECT_EQ(slice->GetResolution(), glm::uvec2(4, 4));

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(TextureSlice, GetAspectRatio)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		const SharedPtr<TextureSlice> slice1 = texture->CreateAndGetSlice({4, 4}, {0, 0});
		EXPECT_NE(slice1.Get(), nullptr);

		const SharedPtr<TextureSlice> slice2 = texture->CreateAndGetSlice({2, 4}, {0, 0});
		EXPECT_NE(slice2.Get(), nullptr);

		const SharedPtr<TextureSlice> slice3 = texture->CreateAndGetSlice({4, 2}, {0, 0});
		EXPECT_NE(slice3.Get(), nullptr);

		EXPECT_EQ(slice1->GetAspectRatio(), 1);
		EXPECT_EQ(slice2->GetAspectRatio(), 0.5f);
		EXPECT_EQ(slice3->GetAspectRatio(), 2);

		EndTest();
	}
}
END_GAME_TEST()
