#pragma once

#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Memory/LazyPtr.h"
#include "Entities/AudioManager.h"
#include "Entities/Grid.h"
#include "Entities/ParticleEmitter.h"
#include "Events/WindowEvents.h"
#include "Game/GameMode.h"

class SnakeGameMode final : public TGL::GameMode, private TGL::WindowResizedEvent
{
private:
    TGL::SharedPtr<TGL::Texture> m_SpriteSheet;

    Grid* m_Grid;
    AudioManager* m_AudioManager;
    ParticleEmitter* m_ParticleEmitter;

    Snake* m_Snake;
    TGL::LazyPtr<Apple> m_Apple;

    bool m_Victory = false;

    f32 m_TickRate;
    f32 m_TickTimer;

public:
    SnakeGameMode();
    ~SnakeGameMode() override = default;

private:
    void OnEarlyUpdate(f32 deltaTime) override;
    void OnLateUpdate(f32 deltaTime) override;

protected:
    void OnWindowResized(glm::uvec2 newResolution) override;

private:
    void RenderImGui();
};
