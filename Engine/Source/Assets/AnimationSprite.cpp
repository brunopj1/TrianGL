#include "AnimationSprite.h"

#include "Core/Services/Private/AssetManager.h"

using namespace TGL;

AnimationSprite::AnimationSprite()
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(AnimationSprite);
}

AnimationSprite::~AnimationSprite()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();
}

SharedPtr<Sprite> AnimationSprite::GetCurrentSprite() const
{
	return m_CurrentSprite;
}

const glm::uvec2& AnimationSprite::GetResolution() const
{
	if (m_CurrentSprite == nullptr)
	{
		return s_DefaultResolution;
	}

	return m_CurrentSprite->GetResolution();
}

bool AnimationSprite::Bind(const u8 slot) const
{
	if (m_CurrentSprite == nullptr)
	{
		return false;
	}

	return m_CurrentSprite->Bind(slot);
}

const glm::mat4& AnimationSprite::GetMatrix() const
{
	if (m_CurrentSprite == nullptr)
	{
		return s_DefaultMatrix;
	}

	return m_CurrentSprite->GetMatrix();
}
