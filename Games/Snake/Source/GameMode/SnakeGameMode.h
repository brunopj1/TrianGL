#pragma once

#include "Implementations/Entities/Camera.h"
#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Entities/Grid.h"
#include "Game/GameMode.h"
#include "Util/Memory/LazyPtr.h"

class SnakeGameMode final : public TGL::GameMode
{
private:
    TGL::Camera* m_Camera;
    glm::uvec2 m_WindowSize;

    std::shared_ptr<TGL::Texture> m_SpriteSheet;

    Grid* m_Grid;
    Snake* m_Snake;
    TGL::LazyPtr<Apple> m_Apple;

    bool m_Victory = false;

    float m_TickRate;
    float m_TickTimer;

public:
    SnakeGameMode();
    ~SnakeGameMode() override = default;

private:
    void OnEarlyUpdate(float deltaTime) override;
    void OnLateUpdate(float deltaTime) override;
};
