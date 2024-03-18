#include "GridMaterial.h"

GridMaterial::GridMaterial()
    : Material("Assets/Shaders/grid.vert", "Assets/Shaders/grid.frag", true),
      GridSize(AddUniform<TGL::Uint2Uniform>("uGridSize")),
      EdgeWidth(AddUniform<TGL::FloatUniform>("uEdgeWidth"))
{}
