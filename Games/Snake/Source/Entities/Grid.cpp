#include "Grid.h"

#include "Components/TextureRenderer.h"
#include "Materials/GridMaterial.h"

using namespace Engine::Core;

Grid::Grid(const glm::uvec2 dimensions)
    : Entity(false)
{
    m_TextureRenderer = AttachComponent<Engine::Components::TextureRenderer>();
    m_TextureRenderer->SetMaterial(Engine::Resources::Material::Load<GridMaterial>());
    m_TextureRenderer->SetZIndex(-1);

    SetDimensions(dimensions);
}

void Grid::SetDimensions(const glm::uvec2& dimensions)
{
    m_Dimensions = dimensions;

    const GridMaterial* material = dynamic_cast<GridMaterial*>(m_TextureRenderer->GetMaterial());
    const float gridResolution = material->GridResolution->GetValue();

    GetTransform().SetScale(glm::vec2(m_Dimensions) + glm::vec2(gridResolution * 0.5f));
}
