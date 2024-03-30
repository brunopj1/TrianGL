#include "AudioPlayer.h"

#include "soloud.h"
#include "Core/ResourceManager.h"
#include "Resources/Sound.h"
#include "soloud_wav.h"

using namespace TGL;

AudioPlayer::AudioPlayer(std::shared_ptr<Sound> sound)
    : Component(true), m_Sound(std::move(sound))
{}

void AudioPlayer::OnUpdate(float deltaTime)
{
    if (m_Handle == -1) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    if (!soloudEngine->isValidVoiceHandle(m_Handle))
    {
        m_Handle = -1;
        m_Status = AudioPlayerStatus::Stopped;
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
    }
    else if (m_Status == AudioPlayerStatus::Paused)
    {
        soloudEngine->setPause(m_Handle, false);
    }

    m_Status = AudioPlayerStatus::Playing;

    soloudEngine->setLooping(m_Handle, m_Looping);
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
}

bool AudioPlayer::GetLooping() const
{
    return m_Looping;
}

void AudioPlayer::SetLooping(const bool looping)
{
    m_Looping = looping;

    // Update the currently playing sound

    if (m_Status == AudioPlayerStatus::Stopped) return;

    SoLoud::Soloud* soloudEngine = ResourceManager::s_SoloudEngine;

    if (soloudEngine == nullptr) return;

    soloudEngine->setLooping(m_Handle, m_Looping);
}
