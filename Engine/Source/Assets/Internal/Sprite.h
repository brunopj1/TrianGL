﻿#pragma once

#include "Core/DataTypes.h"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace TGL
{
	class Sprite
	{
	private:
		friend class SpriteUniform;
		friend class AnimationSprite;

	public:
		Sprite() = default;
		virtual ~Sprite() = default;

	public:
		virtual const glm::uvec2& GetResolution() const = 0;
		f32 GetAspectRatio() const;

	public:
		glm::vec2 CalculateIdealScale() const;
		glm::vec2 CalculateIdealScale(bool keepWidth) const;

	private:
		virtual const glm::mat4& GetMatrix() const = 0;

	private:
		virtual bool Bind(u8 slot) const = 0;
		static void Unbind(u8 slot);
	};
}
