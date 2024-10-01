#pragma once

#include "Core/DataTypes.h"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"

namespace TGL
{
	class Sprite
	{
	private:
		friend class SpriteUniform;

	public:
		Sprite() = default;
		virtual ~Sprite() = default;

	private:
		static void Unbind(u8 slot);
		virtual void Bind(u8 slot) const = 0;

		virtual const glm::mat4& GetMatrix() const = 0;
		virtual const glm::uvec2& GetResolution() const = 0;
	};
}
