#pragma once

#include "Assets/Animation.h"
#include "Assets/Texture.h"
#include "Memory/SharedPtr.h"
#include "glm/gtx/hash.hpp"
#include "glm/vec2.hpp"
#include <unordered_map>

class AssetCollection final
{
private:
	TGL::SharedPtr<TGL::Texture> m_CharactersSpriteSheet;

private:
	std::unordered_map<glm::ivec2, TGL::SharedPtr<TGL::Animation>> m_PlayerIdleAnimations;
	std::unordered_map<glm::ivec2, TGL::SharedPtr<TGL::Animation>> m_PlayerWalkAnimations;

public:
	AssetCollection();

public:
	TGL::SharedPtr<TGL::Animation> GetPlayerIdleAnimation(const glm::ivec2& direction) const;
	TGL::SharedPtr<TGL::Animation> GetPlayerWalkAnimation(const glm::ivec2& direction) const;

private:
	TGL::SharedPtr<TGL::Animation> CreateCharacterAnimation(const TGL::SharedPtr<TGL::Texture>& spriteSheet, u8 spriteSheetWidth, f32 animationDuration, const std::vector<glm::uvec2>& sliceIndices);
};
