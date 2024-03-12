#pragma once

#include "Game/Entity.h"
#include "Grid.h"

class SnakeBody final : public TGL::Entity
{
public:
    SnakeBody(Grid* grid, const glm::ivec2& position);
};
