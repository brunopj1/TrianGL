#pragma once

#include "Game/Entity.h"
#include "Assets/Audio.h"

class AudioManager final : public TGL::Entity
{
private:
    TGL::SharedPtr<TGL::Audio> m_MoveAudio1;
    TGL::SharedPtr<TGL::Audio> m_MoveAudio2;
    TGL::SharedPtr<TGL::Audio> m_HurtAudio;
    TGL::SharedPtr<TGL::Audio> m_AppleAudio;

private:
    TGL::AudioPlayer* m_AudioPlayer;

private:
    bool m_NextMove = true;

public:
    AudioManager();
    ~AudioManager() override = default;

public:
    void PlayMoveAudio();
    void PlayHurtAudio();
    void PlayAppleAudio();
};
