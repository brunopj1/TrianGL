#pragma once

#include "Entities/Camera.h"
#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Entities/Grid.h"
#include "Game/GameMode.h"

// TODO Render the grid

class SnakeGameMode final : public Engine::Game::GameMode
{
private:
    Engine::Entities::Camera* m_Camera;

    Grid* m_Grid;
    Snake* m_Snake;
    Apple* m_Apple;

    float m_TickRate = 0.5f;
    float m_TickTimer = m_TickRate;

public:
    SnakeGameMode();
    ~SnakeGameMode() override = default;

private:
    void OnLateUpdate(float deltaTime) override;
};
