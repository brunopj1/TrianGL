#include "Exceptions/Common/FileNotFoundException.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(Texture, Load)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		EXPECT_THROW(texture->Load("Assets/Textures/dj14n21.png"), FileNotFoundException);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Texture, GetFilePath)
{
	void OnUpdate(f32 deltaTime) override
	{
		const std::string filePath = "Assets/Textures/smile.png";
		const SharedPtr<Texture> texture = Texture::Load(filePath);
		EXPECT_NE(texture.Get(), nullptr);

		EXPECT_NE(texture->GetFilePath().find(filePath), std::string::npos);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Texture, GetResolution)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		EXPECT_EQ(texture->GetResolution(), glm::uvec2(16, 16));

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Texture, CreateSlice)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
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

BEGIN_GAME_TEST(Texture, CreateSliceGrid)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
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

		EXPECT_THROW(texture->CreateSliceGrid({10, 10}, {4, 4}, {4, 4}), std::invalid_argument);

		EXPECT_EQ(texture->GetSliceCount(), 25);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Texture, SliceInfo)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");
		EXPECT_NE(texture.Get(), nullptr);

		const SharedPtr<TextureSlice> slice = texture->CreateAndGetSlice({4, 4}, {0, 0});
		EXPECT_NE(slice.Get(), nullptr);

		EXPECT_EQ(slice->GetTexture(), texture);
		EXPECT_EQ(slice->GetResolution(), glm::uvec2(4, 4));

		EndTest();
	}
}
END_GAME_TEST()
