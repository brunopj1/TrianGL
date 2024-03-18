#pragma once

#include "Resources/Material.h"

namespace TGL
{
    class DefaultMaterial final : public Material
    {
    public:
        TextureUniform* const Texture;
        Float4Uniform* const Color;

    private:
        IntUniform* const IsTextureValid;

    public:
        DefaultMaterial();
        ~DefaultMaterial() override = default;

    protected:
        void OnRenderSetup() const override;
    };
}
