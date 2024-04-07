#pragma once

#include "Assets/Material.h"

class GridMaterial final : public TGL::Material
{
public:
    TGL::Uint2Uniform* const GridSize = AddUniform<TGL::Uint2Uniform>("uGridSize");

public:
    GridMaterial();
};
