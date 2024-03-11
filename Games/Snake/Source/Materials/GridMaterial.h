#pragma once

#include "Resources/Material.h"

class GridMaterial final : public Engine::Material
{
public:
    Engine::Uint2MaterialAttribute* GridSize;
    Engine::FloatMaterialAttribute* EdgeWidth;

public:
    GridMaterial();
};
