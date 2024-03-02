#pragma once

#include "Game/GameMode.h"

class SnakeGameMode final : public Engine::Game::GameMode
{
public:
    SnakeGameMode() = default;
    ~SnakeGameMode() override = default;

    void OnStart() override;
};
