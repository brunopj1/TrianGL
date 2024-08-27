#include "Grid.h"

#include "Implementations/Components/SpriteRenderer.h"
#include "Core/Window.h"
#include "GameMode/RenderingOrder.h"
#include "Implementations/Entities/Camera.h"
#include "Materials/GrassMaterial.h"
#include "glm/glm.hpp"
#include "Util/RandomNumberGenerator.h"
#include <stdexcept>

using namespace TGL;

Grid::Grid(SharedPtr<Texture> spriteSheet, const glm::uvec2 dimensions)
    : Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
    m_SpriteRenderer = AttachComponent<SpriteRenderer>();
    m_SpriteRenderer->SetPivot({0, 0});
    m_SpriteRenderer->SetZIndex(static_cast<i32>(RenderingOrder::Grid));

    const auto material = Material::CreateInstanceOf<GrassMaterial>();
    m_SpriteRenderer->SetMaterial(material);

    material->SpriteSheet->Value = m_SpriteSheet;
    material->SpriteGrassNormal->Value = m_SpriteSheet->GetSlice(0);
    material->SpriteGrassTall->Value = m_SpriteSheet->GetSlice(1);
    material->SpriteGrassFlowers->Value = m_SpriteSheet->GetSlice(2);
    material->SpriteGrassRocks->Value = m_SpriteSheet->GetSlice(3);
    
    Resize(dimensions);
}
glm::uvec2 Grid::GetSize() const
{
    return m_Size;
}

u32 Grid::GetCellCount() const
{
    return m_Size.x * m_Size.y;
}

Entity* Grid::GetCell(const glm::uvec2& position) const
{
    const u32 index = position.y * m_Size.x + position.x;
    return m_Cells.at(index);
}

void Grid::SetCell(const glm::uvec2& position, Entity* entity)
{
    if (position.x >= m_Size.x || position.y >= m_Size.y)
    {
        throw std::runtime_error("Position out of bounds");
    }

    const u32 index = position.y * m_Size.x + position.x;
    m_Cells.at(index) = entity;

    if (entity != nullptr)
    {
        entity->GetTransform().SetPosition(glm::vec2(position) + 0.5f);
    }
}

std::optional<glm::ivec2> Grid::GetRandomFreeCell()
{
    std::vector<u32> freeIndices;

    for (u32 i = 0; i < m_Cells.size(); ++i)
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

    const u32 freeIndexCount = static_cast<u32>(freeIndices.size());
    const u32 randomIndex = freeIndices[m_Random.GetUint(0, freeIndexCount - 1)];
    return glm::ivec2(randomIndex % m_Size.x, randomIndex / m_Size.x);
}

void Grid::Resize(const glm::uvec2& size)
{
    m_Size = size;

    const auto material = CastTo<GrassMaterial>(m_SpriteRenderer->GetMaterial());
    material->GridSize->Value = m_Size;

    const u32 gridSize = m_Size.x * m_Size.y;
    m_Cells.clear();
    m_Cells.resize(gridSize, nullptr);

    Transform& transform = GetTransform();
    transform.SetPosition({0, 0});
    transform.SetScale(glm::vec2(m_Size));
}

void Grid::FocusCamera() const
{
    const auto camera = Camera::GetMainCamera();
    const f32 aspectRatio = camera->GetAspectRatio();

    if (aspectRatio > 1)
    {
        camera->SetVerticalSize(m_Size.y + 0.5f);
    }
    else
    {
        camera->SetHorizontalSize(m_Size.x + 0.5f);
    }

    camera->GetTransform().SetPosition(glm::vec2(m_Size) * 0.5f);
}
