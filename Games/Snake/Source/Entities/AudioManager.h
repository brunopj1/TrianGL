#pragma once

#include "Game/Entity.h"
#include "Resources/Audio.h"

class AudioManager final : public TGL::Entity
{
private:
    std::shared_ptr<TGL::Audio> m_MoveAudio1;
    std::shared_ptr<TGL::Audio> m_MoveAudio2;
    std::shared_ptr<TGL::Audio> m_HurtAudio;
    std::shared_ptr<TGL::Audio> m_AppleAudio;

private:
    TGL::AudioPlayer* m_AudioPlayer;

private:
    bool m_NextMove = true;

public:
    AudioManager();
    ~AudioManager() override = default;

public:
    void PlayMoveAudio();
    void PlayHurtAudio() const;
    void PlayAppleAudio() const;
};
