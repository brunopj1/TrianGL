#include "AssetCollection.h"

#include "Characters/CharacterDirection.h"

using namespace TGL;

AssetCollection::AssetCollection()
{
	TextureParameters textureParams;
	textureParams.Filter = TextureFilterMode::Nearest;
	textureParams.GenerateMipmaps = false;

	m_CharactersSpriteSheet = Texture::Load("Assets/Textures/characters.png", textureParams);
	m_CharactersSpriteSheet->CreateSliceGrid({15, 20}, {0, 4}, {1, 4});

	// Idle animations
	for (u8 dir = 0; dir < 8; dir++)
	{
		const glm::ivec2 dirVec = GetDirectionVector(static_cast<CharacterDirection>(dir));
		m_PlayerIdleAnimations[dirVec] = CreateCharacterAnimation(
			m_CharactersSpriteSheet,
			8,
			1.0f,
			{{dir, 2}});
	}

	// Walk animations
	for (u8 dir = 0; dir < 8; dir++)
	{
		const glm::ivec2 dirVec = GetDirectionVector(static_cast<CharacterDirection>(dir));
		m_PlayerWalkAnimations[dirVec] = CreateCharacterAnimation(
			m_CharactersSpriteSheet,
			8,
			0.5f,
			{{dir, 1}, {dir, 2}, {dir, 3}, {dir, 2}});
	}
}

SharedPtr<Animation> AssetCollection::GetPlayerIdleAnimation(const glm::ivec2& direction) const
{
	return m_PlayerIdleAnimations.at(direction);
}

SharedPtr<Animation> AssetCollection::GetPlayerWalkAnimation(const glm::ivec2& direction) const
{
	return m_PlayerWalkAnimations.at(direction);
}

SharedPtr<Animation> AssetCollection::CreateCharacterAnimation(const SharedPtr<Texture>& spriteSheet, const u8 spriteSheetWidth, const f32 animationDuration, const std::vector<glm::uvec2>& sliceIndices) // NOLINT(CppMemberFunctionMayBeStatic)
{
	SharedPtr<Animation> animation = Animation::Create();
	const f32 frameDuration = animationDuration / sliceIndices.size();

	for (const glm::uvec2& sliceIdx : sliceIndices)
	{
		const u32 sliceIndex = sliceIdx.y * spriteSheetWidth + sliceIdx.x;
		const SharedPtr<TextureSlice> slice = spriteSheet->GetSlice(sliceIndex);
		animation->AddFrame(slice, frameDuration);
	}

	return animation;
}
