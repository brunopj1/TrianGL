#pragma once

#include "Resources/Material.h"

class GridMaterial final : public TGL::Material
{
public:
    TGL::Uint2MaterialAttribute* GridSize;
    TGL::FloatMaterialAttribute* EdgeWidth;

public:
    GridMaterial();
};
