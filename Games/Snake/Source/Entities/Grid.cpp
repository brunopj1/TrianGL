#include "Grid.h"

#include "Components/TextureRenderer.h"
#include "Materials/GridMaterial.h"

using namespace Engine;

Grid::Grid(const glm::uvec2 dimensions)
    : Entity(false)
{
    m_TextureRenderer = AttachComponent<TextureRenderer>();
    m_TextureRenderer->SetMaterial(Material::Load<GridMaterial>());
    m_TextureRenderer->SetPivot({0, 0});
    m_TextureRenderer->SetZIndex(-1);

    Resize(dimensions);
}

glm::uvec2 Grid::GetSize() const
{
    return m_Size;
}

unsigned Grid::GetCellCount() const
{
    return m_Size.x * m_Size.y;
}

void Grid::Resize(const glm::uvec2& size)
{
    m_Size = size;
    const unsigned gridSize = m_Size.x * m_Size.y;

    m_Cells.clear();
    m_Cells.resize(gridSize, nullptr);

    const GridMaterial* material = dynamic_cast<GridMaterial*>(m_TextureRenderer->GetMaterial());
    material->GridSize->SetValue(m_Size);
    const float edgeWidth = material->EdgeWidth->GetValue();

    Transform& transform = GetTransform();
    transform.SetPosition(glm::vec2(-edgeWidth * 0.5f));
    transform.SetScale(glm::vec2(m_Size) + edgeWidth);
}

Entity* Grid::GetCell(const glm::uvec2& position) const
{
    const unsigned index = position.y * m_Size.x + position.x;
    return m_Cells.at(index);
}

Entity* Grid::SetCell(const glm::uvec2& position, Entity* entity)
{
    const unsigned index = position.y * m_Size.x + position.x;
    Entity* previousEntity = m_Cells.at(index);

    m_Cells.at(index) = entity;

    if (entity != nullptr)
    {
        entity->GetTransform().SetPosition(glm::vec2(position) + 0.5f);
    }

    return previousEntity;
}

std::optional<glm::ivec2> Grid::GetRandomFreeCell() const
{
    std::vector<unsigned> freeIndices;

    for (unsigned i = 0; i < m_Cells.size(); ++i)
    {
        if (m_Cells[i] == nullptr)
        {
            freeIndices.push_back(i);
        }
    }

    if (freeIndices.empty())
    {
        return std::nullopt;
    }

    const unsigned randomIndex = freeIndices[rand() % freeIndices.size()]; // NOLINT
    return glm::ivec2(randomIndex % m_Size.x, randomIndex / m_Size.x);
}
