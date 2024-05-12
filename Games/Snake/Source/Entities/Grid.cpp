#include "Grid.h"

#include "Implementations/Components/SpriteRenderer.h"
#include "Core/Window.h"
#include "Implementations/Entities/Camera.h"
#include "Materials/GridMaterial.h"
#include "glm/glm.hpp"
#include "Util/RandomNumberGenerator.h"
#include <stdexcept>

using namespace TGL;

Grid::Grid(const glm::uvec2 dimensions)
    : Entity(false)
{
    m_SpriteRenderer = AttachComponent<SpriteRenderer>();
    m_SpriteRenderer->SetMaterial(Material::CreateInstanceOf<GridMaterial>());
    m_SpriteRenderer->SetPivot({0, 0});
    m_SpriteRenderer->SetZIndex(-1);

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

Entity* Grid::GetCell(const glm::uvec2& position) const
{
    const unsigned index = position.y * m_Size.x + position.x;
    return m_Cells.at(index);
}

void Grid::SetCell(const glm::uvec2& position, Entity* entity)
{
    if (position.x >= m_Size.x || position.y >= m_Size.y)
    {
        throw std::runtime_error("Position out of bounds");
    }

    const unsigned index = position.y * m_Size.x + position.x;
    m_Cells.at(index) = entity;

    if (entity != nullptr)
    {
        entity->GetTransform().SetPosition(glm::vec2(position) + 0.5f);
    }
}

std::optional<glm::ivec2> Grid::GetRandomFreeCell()
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

    const unsigned randomIndex = freeIndices[m_Random.GetUint(0, freeIndices.size() - 1)];
    return glm::ivec2(randomIndex % m_Size.x, randomIndex / m_Size.x);
}

void Grid::Resize(const glm::uvec2& size)
{
    m_Size = size;

    const auto material = CastTo<GridMaterial>(m_SpriteRenderer->GetMaterial());
    material->GridSize->Value = m_Size;

    const unsigned gridSize = m_Size.x * m_Size.y;
    m_Cells.clear();
    m_Cells.resize(gridSize, nullptr);

    Transform& transform = GetTransform();
    transform.SetPosition({0, 0});
    transform.SetScale(glm::vec2(m_Size));
}

void Grid::FocusCamera() const
{
    const auto camera = Camera::GetMainCamera();
    const float aspectRatio = camera->GetAspectRatio();

    if (aspectRatio > 1)
    {
        camera->SetVerticalSize(m_Size.y + 0.5f);
    }
    else
    {
        camera->SetHorizontalSize(m_Size.x + 0.5f);
    }

    camera->GetTransform().SetPosition(glm::vec3(m_Size, 0) * 0.5f);
}
