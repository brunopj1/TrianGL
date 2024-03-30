#include "AudioManager.h"

#include "Implementations/Components/AudioPlayer.h"

AudioManager::AudioManager()
    : Entity(false)
{
    m_MoveSound1 = TGL::Sound::Load("Assets/Audio/move1.wav");
    m_MoveSound2 = TGL::Sound::Load("Assets/Audio/move2.wav");
    m_HurtSound = TGL::Sound::Load("Assets/Audio/hurt.wav");
    m_AppleSound = TGL::Sound::Load("Assets/Audio/apple.wav");

    m_AudioPlayer = AttachComponent<TGL::AudioPlayer>();
}

void AudioManager::PlayMoveSound()
{
    m_AudioPlayer->SetSound(m_NextMove ? m_MoveSound1 : m_MoveSound2);
    m_AudioPlayer->Play();

    m_NextMove = !m_NextMove;
}

void AudioManager::PlayHurtSound() const
{
    m_AudioPlayer->SetSound(m_HurtSound);
    m_AudioPlayer->Play();
}

void AudioManager::PlayAppleSound() const
{
    m_AudioPlayer->SetSound(m_AppleSound);
    m_AudioPlayer->Play();
}
