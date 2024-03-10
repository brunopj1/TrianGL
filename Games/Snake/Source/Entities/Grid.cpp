#include "Grid.h"

#include "Services/EntityManager.h"
#include "Components/TextureRenderer.h"
#include "Materials/GridMaterial.h"
#include "Services/ResourceManager.h"

using namespace Engine::Services;

Grid::Grid(const glm::uvec2 dimensions)
    : Entity(false)
{
    m_TextureRenderer = AttachComponent<Engine::Components::TextureRenderer>();
    m_TextureRenderer->SetMaterial(ResourceManager::LoadMaterial<GridMaterial>());
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
