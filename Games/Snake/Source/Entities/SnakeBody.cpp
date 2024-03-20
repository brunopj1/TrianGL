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

glm::ivec2 SnakeBody::GetBackDirection() const
{
    return m_BackDirection;
}

void SnakeBody::SetAsHead(const glm::ivec2& direction)
{
    m_Type = SnakeBodyType::Head;
    m_FrontDirection = direction;

    UpdateTexture();
}

void SnakeBody::SetAsBody()
{
    m_Type = SnakeBodyType::Body;

    UpdateTexture();
}

void SnakeBody::SetAsTail()
{
    m_Type = SnakeBodyType::Tail;
    m_BackDirection = m_FrontDirection;

    UpdateTexture();
}

void SnakeBody::UpdateTexture()
{
    // Find the correct texture slice

    std::shared_ptr<TextureSlice> texture = nullptr;

    if (m_Type == SnakeBodyType::Tail)
    {
        texture = m_Texture->GetSlice(3);
    }
    else
    {
        int idx = m_Type == SnakeBodyType::Head ? 0 : 4;

        const int crossMoveDirection = m_BackDirection.x * m_FrontDirection.y - m_BackDirection.y * m_FrontDirection.x;
        idx += crossMoveDirection < 0 ? 1 : crossMoveDirection > 0 ? 2 : 0;

        texture = m_Texture->GetSlice(idx);
    }

    m_TextureRenderer->GetMaterial()->As<DefaultMaterial>()->Texture->Value = texture;

    // Rotate the texture

    const float angle = (m_BackDirection.y == -1) * 180.0f - glm::sign(m_BackDirection.x) * 90.0f;
    GetTransform().SetRotationDeg(angle);
}
