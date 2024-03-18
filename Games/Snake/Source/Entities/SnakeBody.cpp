#include "SnakeBody.h"

#include <utility>

#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"

using namespace TGL;

SnakeBody::SnakeBody(Grid* grid, std::shared_ptr<Texture> texture, const glm::ivec2& position, const glm::ivec2& direction)
    : Entity(false), m_Type(SnakeBodyType::Head), m_BackDirection(direction), m_FrontDirection(direction), m_Texture(std::move(texture))
{
    m_TextureRenderer = AttachComponent<TextureRenderer>();
    m_TextureRenderer->UseDefaultMaterial();

    grid->SetCell(position, this);

    UpdateTexture();
}

void SnakeBody::Modify(const SnakeBodyType type, const glm::ivec2& frontDirection, const glm::ivec2& backDirection)
{
    m_Type = type;
    if (frontDirection != glm::ivec2(0)) m_FrontDirection = frontDirection;
    if (backDirection != glm::ivec2(0)) m_BackDirection = backDirection;

    UpdateTexture();
}

void SnakeBody::UpdateTexture()
{
    // Find the correct texture

    std::shared_ptr<TextureSlice> texture = nullptr;

    if (m_Type == SnakeBodyType::Tail)
    {
        texture = m_Texture->GetSlice(6);
    }
    else
    {
        int idx = m_Type == SnakeBodyType::Head ? 0 : 3;

        const int crossMoveDirection = m_BackDirection.x * m_FrontDirection.y - m_BackDirection.y * m_FrontDirection.x;
        idx += crossMoveDirection < 0 ? 1 : crossMoveDirection > 0 ? 2 : 0;

        texture = m_Texture->GetSlice(idx);
    }

    m_TextureRenderer->GetMaterial()->As<DefaultMaterial>()->GetTextureAttr()->SetValue(texture);

    // Rotate the texture

    //const int crossMoveDirection = m_BackDirection.x * m_FrontDirection.y - m_BackDirection.y * m_FrontDirection.x;
    //if (crossMoveDirection > 0) GetTransform().SetScale({-1, 1});

    const float angle = (m_BackDirection.y == -1) * 180.0f - glm::sign(m_BackDirection.x) * 90.0f;
    GetTransform().SetRotationDeg(angle);
}
