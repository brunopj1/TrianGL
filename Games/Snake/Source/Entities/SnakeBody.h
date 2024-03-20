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
    glm::ivec2 GetBackDirection() const;

public:
    void SetAsHead(const glm::ivec2& direction);
    void SetAsBody();
    void SetAsTail();

private:
    void UpdateTexture();
};
