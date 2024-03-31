#include "AudioPlayer.h"

#include "soloud.h"
#include "Core/ResourceManager.h"
#include "Resources/Sound.h"
#include "soloud_wav.h"
#include <utility>

using namespace TGL;

AudioPlayer::AudioPlayer(std::shared_ptr<Sound> sound)
    : Component(true), m_Sound(std::move(sound))
{}

AudioPlayer::~AudioPlayer()
{
    Stop();
}

void AudioPlayer::OnUpdate(float deltaTime)
{
    if (m_Handle == -1) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    if (!soloudEngine->isValidVoiceHandle(m_Handle))
    {
        m_Status = AudioPlayerStatus::Stopped;

        m_Handle = -1;

        m_Sound->RemovePlayer(this);
    }
}

std::shared_ptr<Sound> AudioPlayer::GetSound() const
{
    return m_Sound;
}

void AudioPlayer::SetSound(std::shared_ptr<Sound> sound)
{
    Stop();

    m_Sound = std::move(sound);
}

AudioPlayerStatus AudioPlayer::GetStatus() const
{
    return m_Status;
}

void AudioPlayer::Play()
{
    if (m_Status == AudioPlayerStatus::Playing) return;

    if (m_Sound == nullptr) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    if (m_Status == AudioPlayerStatus::Stopped)
    {
        m_Handle = soloudEngine->play(*m_Sound->m_SoloudSound);

        m_Sound->AddPlayer(this);

        UpdateCurrentSoundVolume();
        UpdateCurrentSoundLoop();
    }
    else if (m_Status == AudioPlayerStatus::Paused)
    {
        soloudEngine->setPause(m_Handle, false);
    }

    m_Status = AudioPlayerStatus::Playing;
}

void AudioPlayer::Pause()
{
    if (m_Status != AudioPlayerStatus::Playing) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    soloudEngine->setPause(m_Handle, true);

    m_Status = AudioPlayerStatus::Paused;
}

void AudioPlayer::Stop()
{
    if (m_Status == AudioPlayerStatus::Stopped) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    soloudEngine->stop(m_Handle);

    m_Status = AudioPlayerStatus::Stopped;

    m_Handle = -1;

    m_Sound->RemovePlayer(this);
}

float AudioPlayer::GetVolume() const
{
    return m_Volume;
}

void AudioPlayer::SetVolume(const float volume)
{
    m_Volume = volume < 0.0f ? 0.0f : volume;

    if (m_Status == AudioPlayerStatus::Stopped) return;

    UpdateCurrentSoundVolume();
}

float AudioPlayer::GetFinalVolume() const
{
    return m_Volume * m_Sound->GetVolume();
}

bool AudioPlayer::GetLoop() const
{
    return m_Loop;
}

void AudioPlayer::SetLoop(const bool loop)
{
    m_Loop = loop;

    if (m_Status == AudioPlayerStatus::Stopped) return;

    UpdateCurrentSoundLoop();
}

void AudioPlayer::UpdateCurrentSoundVolume() const
{
    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    soloudEngine->setVolume(m_Handle, GetFinalVolume());
}

void AudioPlayer::UpdateCurrentSoundLoop() const
{
    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    soloudEngine->setLooping(m_Handle, m_Loop);
}
