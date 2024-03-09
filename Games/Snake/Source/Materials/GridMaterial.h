#pragma once
#include "Resources/Material.h"

class GridMaterial final : public Engine::Resources::Material
{
public:
    Engine::Resources::FloatMaterialAttribute* GridResolution;

public:
    GridMaterial();
};
