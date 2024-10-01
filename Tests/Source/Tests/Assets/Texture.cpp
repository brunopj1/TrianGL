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
