#pragma once

#include "Game/Entity.h"

enum class GridPosition
{
    Empty = 0,
    Apple,
    Snake,
    SnakeEnd
};

class Grid final : public Engine::Game::Entity
{
private:
    glm::uvec2 m_Dimensions;

private:
    Engine::Components::TextureRenderer* m_TextureRenderer = nullptr;

public:
    Grid(glm::uvec2 dimensions);
    ~Grid() override = default;

public:
    void SetDimensions(const glm::uvec2& dimensions);
};
