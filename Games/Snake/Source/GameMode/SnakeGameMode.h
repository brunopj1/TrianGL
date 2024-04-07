#pragma once

#include "Entities/Snake.h"
#include "Entities/Apple.h"
#include "Entities/AudioManager.h"
#include "Entities/Grid.h"
#include "Events/WindowEvents.h"
#include "Game/GameMode.h"
#include "Assets/Audio.h"
#include "Util/Memory/LazyPtr.h"

class SnakeGameMode final : public TGL::GameMode, private TGL::WindowResizedEvent
{
private:
    std::shared_ptr<TGL::Texture> m_SpriteSheet;

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
