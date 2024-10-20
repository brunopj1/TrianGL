#include "SnakeBody.h"

#include "GameMode/RenderingOrder.h"
#include "Implementations/Materials/DefaultSpriteMaterial.h"
#include "Rendering/SpriteRenderer.h"
#include <utility>

using namespace TGL;

SnakeBody::SnakeBody(Grid* grid, SharedPtr<Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction)
	: Entity(false), m_Type(SnakeBodyType::Head), m_BackDirection(direction), m_FrontDirection(direction), m_SpriteSheet(std::move(spriteSheet))
{
	m_SpriteRenderer = AttachComponent<SpriteRenderer>();
	m_SpriteRenderer->UseDefaultMaterial();
	m_SpriteRenderer->SetZIndex(static_cast<i32>(RenderingOrder::Snake));

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

	SharedPtr<TextureSlice> texture = nullptr;

	if (m_Type == SnakeBodyType::Tail)
	{
		texture = m_SpriteSheet->GetSlice(7);
	}
	else
	{
		i32 idx = m_Type == SnakeBodyType::Head ? 4 : 8;

		const i32 crossMoveDirection = m_BackDirection.x * m_FrontDirection.y - m_BackDirection.y * m_FrontDirection.x;
		if (crossMoveDirection < 0)
		{
			idx += 1;
		}
		else if (crossMoveDirection > 0)
		{
			idx += 2;
		}

		texture = m_SpriteSheet->GetSlice(idx);
	}

	const auto material = CastTo<DefaultSpriteMaterial>(m_SpriteRenderer->GetMaterial());
	material->Sprite->Value = texture;

	// Rotate the texture

	const f32 angle = (m_BackDirection.y == -1) * 180.0f - glm::sign(m_BackDirection.x) * 90.0f;
	GetTransform().SetRotationDeg(angle);
}
