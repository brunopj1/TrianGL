#pragma once

#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Memory/LazyPtr.h"
#include "Entities/AudioManager.h"
#include "Entities/Grid.h"
#include "Events/WindowEvents.h"
#include "Game/GameMode.h"

class SnakeGameMode final : public TGL::GameMode, private TGL::WindowResizedEvent
{
private:
    TGL::SharedPtr<TGL::Texture> m_SpriteSheet;

    Grid* m_Grid;
    AudioManager* m_AudioManager;

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

protected:
    void OnWindowResized(glm::uvec2 newResolution) override;

#ifdef DEBUG

private:
    void RenderImGui();

#endif
};
