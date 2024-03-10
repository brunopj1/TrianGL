﻿#include "GridMaterial.h"

GridMaterial::GridMaterial()
    : Material("Assets/Shaders/grid.vert", "Assets/Shaders/grid.frag", true)
{
    GridResolution = AddAttribute<Engine::FloatMaterialAttribute>("uGridResolution");
    GridResolution->SetValue(0.02f);
}
