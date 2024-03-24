#pragma once

#include "Resources/Material.h"

namespace TGL
{
    class DefaultMaterial final : public Material
    {
    public:
        TextureUniform* const Texture = AddUniform<TextureUniform>("uTexture");
        Float4Uniform* const Color = AddUniform<Float4Uniform>("uColor");

    private:
        IntUniform* const IsTextureValid = AddUniform<IntUniform>("uIsTextureValid");

    public:
        DefaultMaterial();
        ~DefaultMaterial() override = default;

    protected:
        void OnRenderSetup() const override;
    };
}
