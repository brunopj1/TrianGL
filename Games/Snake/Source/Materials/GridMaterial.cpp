#include "GridMaterial.h"

GridMaterial::GridMaterial()
    : Material("Assets/Shaders/grid.vert", "Assets/Shaders/grid.frag", true)
{
    GridSize = AddAttribute<TGL::Uint2MaterialAttribute>("uGridSize");
    GridSize->SetValue({5, 5});

    EdgeWidth = AddAttribute<TGL::FloatMaterialAttribute>("uEdgeWidth");
    EdgeWidth->SetValue(0.02f);
}
