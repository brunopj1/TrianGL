#pragma once

#include <Assets/Material.h>

namespace TGL
{
	class DefaultSpriteMaterial final : public Material
	{
	public:
		SpriteUniform* const Sprite = AddUniform<SpriteUniform>("uSprite");
		FVec4Uniform* const Color = AddUniform<FVec4Uniform>("uColor");

	private:
		IntUniform* const IsSpriteValid = AddUniform<IntUniform>("uIsSpriteValid");

	public:
		DefaultSpriteMaterial();
		~DefaultSpriteMaterial() override = default;

	protected:
		void OnRenderSetup() override;
	};
}
