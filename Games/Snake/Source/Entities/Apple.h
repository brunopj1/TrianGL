#pragma once

#include "Game/Entity.h"

class Apple final : public Engine::Entity
{
public:
    Apple();
    ~Apple() override = default;

protected:
    int GetOrderOfExecution() const override;
};
