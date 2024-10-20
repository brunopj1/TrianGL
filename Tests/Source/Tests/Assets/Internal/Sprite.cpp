#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(Sprite, CalculateIdealScale)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Texture> texture = Texture::Load("Assets/Textures/smile.png");

		const SharedPtr<TextureSlice> slice1 = texture->CreateAndGetSlice({4, 4}, {0, 0});

		const glm::vec2 idealScale1 = slice1->CalculateIdealScale();
		EXPECT_NEAR(idealScale1.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale1.y, 1.0f, 0.001f);

		const glm::vec2 idealScale1True = slice1->CalculateIdealScale(true);
		EXPECT_NEAR(idealScale1True.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale1True.y, 1.0f, 0.001f);

		const glm::vec2 idealScale1False = slice1->CalculateIdealScale(false);
		EXPECT_NEAR(idealScale1False.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale1False.y, 1.0f, 0.001f);

		const SharedPtr<TextureSlice> slice2 = texture->CreateAndGetSlice({4, 8}, {0, 0});

		const glm::vec2 idealScale2 = slice2->CalculateIdealScale();
		EXPECT_NEAR(idealScale2.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale2.y, 2.0f, 0.001f);

		const glm::vec2 idealScale2True = slice2->CalculateIdealScale(true);
		EXPECT_NEAR(idealScale2True.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale2True.y, 2.0f, 0.001f);

		const glm::vec2 idealScale2False = slice2->CalculateIdealScale(false);
		EXPECT_NEAR(idealScale2False.x, 0.5f, 0.001f);
		EXPECT_NEAR(idealScale2False.y, 1.0f, 0.001f);

		const SharedPtr<TextureSlice> slice3 = texture->CreateAndGetSlice({4, 2}, {0, 0});

		const glm::vec2 idealScale3 = slice3->CalculateIdealScale();
		EXPECT_NEAR(idealScale3.x, 2.0f, 0.001f);
		EXPECT_NEAR(idealScale3.y, 1.0f, 0.001f);

		const glm::vec2 idealScale3True = slice3->CalculateIdealScale(true);
		EXPECT_NEAR(idealScale3True.x, 1.0f, 0.001f);
		EXPECT_NEAR(idealScale3True.y, 0.5f, 0.001f);

		const glm::vec2 idealScale3False = slice3->CalculateIdealScale(false);
		EXPECT_NEAR(idealScale3False.x, 2.0f, 0.001f);
		EXPECT_NEAR(idealScale3False.y, 1.0f, 0.001f);

		EndTest();
	}
}
END_GAME_TEST()
