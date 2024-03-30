#pragma once

#include "Game/Entity.h"
#include "Resources/Sound.h"

class AudioManager final : public TGL::Entity
{
private:
    std::shared_ptr<TGL::Sound> m_MoveSound1;
    std::shared_ptr<TGL::Sound> m_MoveSound2;
    std::shared_ptr<TGL::Sound> m_HurtSound;
    std::shared_ptr<TGL::Sound> m_AppleSound;

private:
    TGL::AudioPlayer* m_AudioPlayer;

private:
    bool m_NextMove = true;

public:
    AudioManager();
    ~AudioManager() override = default;

public:
    void PlayMoveSound();
    void PlayHurtSound() const;
    void PlayAppleSound() const;
};
