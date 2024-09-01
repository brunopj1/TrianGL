#include "AudioManager.h"

#include "Implementations/Components/AudioPlayer.h"

AudioManager::AudioManager()
    : Entity(false)
{
    m_MoveAudio1 = TGL::Audio::Load("Assets/Audio/move1.wav");
    m_MoveAudio2 = TGL::Audio::Load("Assets/Audio/move2.wav");
    m_HurtAudio = TGL::Audio::Load("Assets/Audio/hurt.wav");
    m_AppleAudio = TGL::Audio::Load("Assets/Audio/apple.wav");

    m_AudioPlayer = AttachComponent<TGL::AudioPlayer>();
}

void AudioManager::PlayMoveAudio()
{
    m_AudioPlayer->SetAudio(m_NextMove ? m_MoveAudio1 : m_MoveAudio2);
    m_AudioPlayer->Play();

    m_NextMove = !m_NextMove;
}

void AudioManager::PlayHurtAudio()
{
    m_AudioPlayer->SetAudio(m_HurtAudio);
    m_AudioPlayer->Play();

    m_NextMove = !m_NextMove;
}

void AudioManager::PlayAppleAudio()
{
    m_AudioPlayer->SetAudio(m_AppleAudio);
    m_AudioPlayer->Play();

    m_NextMove = !m_NextMove;
}
