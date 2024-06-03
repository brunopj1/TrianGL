#pragma once

#include "Assets/Material.h"

// TODO add texture like in DefaultSpriteMaterial
// TODO add bool for rounded particles

namespace TGL
{
    class DefaultParticleMaterial final : public Material
    {
    public:
        DefaultParticleMaterial();
        ~DefaultParticleMaterial() override = default;
    };
}
