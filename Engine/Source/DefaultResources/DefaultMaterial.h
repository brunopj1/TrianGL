#pragma once

#include "Resources/Material.h"

namespace Engine::DefaultResources
{
    class DefaultMaterial final : public Resources::Material
    {
    public:
        DefaultMaterial();
        ~DefaultMaterial() override = default;
    };
}
