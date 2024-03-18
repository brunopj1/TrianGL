#pragma once

#include "Game/Entity.h"
#include "Grid.h"
#include "Resources/Texture.h"

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
    TGL::TextureRenderer* m_TextureRenderer;

private:
    std::shared_ptr<TGL::Texture> m_Texture;

public:
    SnakeBody(Grid* grid, std::shared_ptr<TGL::Texture> texture, const glm::ivec2& position, const glm::ivec2& direction);

public:
    void Modify(SnakeBodyType type, const glm::ivec2& frontDirection = {0, 0}, const glm::ivec2& backDirection = {0, 0});

private:
    void UpdateTexture();
};
