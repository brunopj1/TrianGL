#pragma once

#include <format>
#include <stdexcept>

namespace TGL
{
	class IncompatibleMaterialException final : public std::runtime_error
	{
	public:
		IncompatibleMaterialException(const bool isSpriteRenderer)
			: std::runtime_error(std::format("The specified material is not compatible with the %s",
											 isSpriteRenderer ? "Sprite Renderer" : "Particle System")) {}
	};
}
