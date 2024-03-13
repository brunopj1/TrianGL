#pragma once

#include "Entities/Camera.h"
#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Entities/Grid.h"
#include "Game/GameMode.h"

class SnakeGameMode final : public TGL::GameMode
{
private:
    TGL::Camera* m_Camera;
    glm::uvec2 m_WindowSize;

    Grid* m_Grid;
    Snake* m_Snake;
    Apple* m_Apple;

    float m_TickRate = 0.5f;
    float m_TickTimer = m_TickRate;

public:
    SnakeGameMode();
    ~SnakeGameMode() override = default;

private:
    void OnEarlyUpdate(float deltaTime) override;
    void OnLateUpdate(float deltaTime) override;

private:
    void FocusCameraOnGrid() const;
};
