#pragma once

#include "Assets/Material.h"

// TODO add texture like in DefaultSpriteMaterial
// TODO add bool for rounded particles

namespace TGL
{
    class DefaultParticleMaterial final : public Material
    {
    public:
        FloatUniform* const BorderRadius = AddUniform<FloatUniform>("uBorderRadius");
        SpriteUniform* const Sprite = AddUniform<SpriteUniform>("uSprite");

    private:
        IntUniform* const IsSpriteValid = AddUniform<IntUniform>("uIsSpriteValid");
        
    public:
        DefaultParticleMaterial();
        ~DefaultParticleMaterial() override = default;

    protected:
        void OnRenderSetup() const override;
    };
}
