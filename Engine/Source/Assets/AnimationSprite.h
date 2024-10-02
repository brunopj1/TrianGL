#pragma once

#include "Internal/Sprite.h"
#include "Memory/SharedPtr.h"

namespace TGL
{
	class AnimationSprite final : public Sprite
	{
	private:
		friend class AssetManager;
		friend class Animator;

	private:
		SharedPtr<Sprite> m_CurrentSprite;

	private:
		static inline glm::mat4 s_DefaultMatrix = glm::mat4(1.0f);
		static inline glm::uvec2 s_DefaultResolution = {0, 0};

	public:
		AnimationSprite();
		~AnimationSprite() override;

	public:
		SharedPtr<Sprite> GetCurrentSprite() const;

	private:
		bool Bind(u8 slot) const override;

	private:
		const glm::mat4& GetMatrix() const override;
		const glm::uvec2& GetResolution() const override;
	};
}
