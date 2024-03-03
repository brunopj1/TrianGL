#pragma once

#include "Game/Entity.h"

class FoodEntity final : public Engine::Game::Entity
{
public:
    FoodEntity();
    ~FoodEntity() override = default;

protected:
    int GetOrderOfExecution() const override;

protected:
    void OnStart() override;
};
