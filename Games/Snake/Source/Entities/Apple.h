#pragma once

#include "Game/Entity.h"
#include "Grid.h"
#include "SnakeBody.h"

class Apple final : public Engine::Entity
{
public:
    Apple(Grid* grid);
    ~Apple() override = default;

protected:
    int GetOrderOfExecution() const override;

public:
    void RandomizePosition(Grid* grid);
};
