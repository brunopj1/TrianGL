﻿#pragma once

#include "Assets/Texture.h"
#include "Game/Entity.h"
#include "Grid.h"

enum class SnakeBodyType
{
	Head,
	Body,
	Tail
};

class SnakeBody final : public TGL::Entity
{
private:
	SnakeBodyType m_Type;
	glm::ivec2 m_BackDirection;
	glm::ivec2 m_FrontDirection;

private:
	TGL::SpriteRenderer* m_SpriteRenderer;

private:
	TGL::SharedPtr<TGL::Texture> m_SpriteSheet;

public:
	SnakeBody(Grid* grid, TGL::SharedPtr<TGL::Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction);

public:
	glm::ivec2 GetBackDirection() const;

public:
	void SetAsHead(const glm::ivec2& direction);
	void SetAsBody();
	void SetAsTail();

private:
	void UpdateTexture();
};
