#include "AnimationPlaygroundGameMode.h"

#include "Assets/Texture.h"
#include "Entities/AnimationTester.h"
#include "Entities/AnimatorTester.h"
#include <General/Camera.h>

using namespace TGL;

AnimationPlaygroundGameMode::AnimationPlaygroundGameMode()
{
	Camera* camera = SpawnEntity<Camera>(true);

	// Texture

	TextureParameters params;
	params.GenerateMipmaps = false;
	params.Filter = TextureFilterMode::Nearest;

	SharedPtr<Texture> texture = Texture::Load("Assets/Textures/spritesheet.png", params);

	// Animation 1

	std::vector<SharedPtr<Sprite>> animation1Sprites;

	for (u32 i = 0; i < 6; i++)
	{
		SharedPtr<Sprite> sprite = texture->CreateAndGetSlice({16, 16}, {16 * i, 0});
		animation1Sprites.push_back(sprite);
	}

	SpawnEntity<AnimationTester>(animation1Sprites);

	// Animation 2

	std::vector<SharedPtr<Sprite>> animation2Sprites;

	for (u32 i = 0; i < 8; i++)
	{
		SharedPtr<Sprite> sprite = texture->CreateAndGetSlice({16, 16}, {16 * i, 16});
		animation2Sprites.push_back(sprite);
	}

	SpawnEntity<AnimationTester>(animation2Sprites);

	// Animators

	SpawnEntity<AnimatorTester>(glm::vec2(1.0f, 1.5f));
	SpawnEntity<AnimatorTester>(glm::vec2(1.0f, -1.5f));
}
