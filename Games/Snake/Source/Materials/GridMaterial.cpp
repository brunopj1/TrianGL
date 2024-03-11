#include "GridMaterial.h"

GridMaterial::GridMaterial()
    : Material("Assets/Shaders/grid.vert", "Assets/Shaders/grid.frag", true)
{
    GridSize = AddAttribute<Engine::Uint2MaterialAttribute>("uGridSize");
    GridSize->SetValue({5, 5});

    EdgeWidth = AddAttribute<Engine::FloatMaterialAttribute>("uEdgeWidth");
    EdgeWidth->SetValue(0.02f);
}
