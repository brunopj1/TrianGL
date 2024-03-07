#pragma once

#include "Game/Entity.h"

class SnakeEntity final : public Engine::Game::Entity
{
public:
    SnakeEntity();
    ~SnakeEntity() override = default;

protected:
    int GetOrderOfExecution() const override;

protected:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;
};
