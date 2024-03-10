#pragma once

#include "Resources/Material.h"

class GridMaterial final : public Engine::Material
{
public:
    Engine::FloatMaterialAttribute* GridResolution;

public:
    GridMaterial();
};
