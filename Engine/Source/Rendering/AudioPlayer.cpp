﻿#include "Core/Services/Backends/AudioBackend.h"
#include <Assets/Audio.h>
#include <Core/Services/Private/AssetManager.h>
#include <Rendering/AudioPlayer.h>
#include <utility>

using namespace TGL;

AudioPlayer::AudioPlayer(SharedPtr<Audio> audio)
	: Component(true, I32_MIN), m_Audio(std::move(audio)) {}

AudioPlayer::~AudioPlayer()
{
	Stop();
}

SharedPtr<Audio> AudioPlayer::GetAudio() const
{
	return m_Audio;
}

void AudioPlayer::SetAudio(SharedPtr<Audio> audio)
{
	if (m_Audio == audio)
	{
		return;
	}

	Stop();

	m_Audio = std::move(audio);
}

AudioPlayerStatus AudioPlayer::GetStatus() const
{
	return m_Status;
}

void AudioPlayer::Play()
{
	if (m_Status == AudioPlayerStatus::Playing)
	{
		return;
	}

	if (m_Audio == nullptr)
	{
		return;
	}

	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();

	if (m_Status == AudioPlayerStatus::Stopped)
	{
		m_Handle = audioBackend.PlayAudio(soloudEngine, m_Audio->m_SoloudAudio);

		m_Audio->AddPlayer(this);

		UpdateCurrentAudioVolume();
		UpdateCurrentAudioLoop();
	}
	else if (m_Status == AudioPlayerStatus::Paused)
	{
		audioBackend.ResumeAudio(soloudEngine, m_Handle);
	}

	m_Status = AudioPlayerStatus::Playing;
}

void AudioPlayer::Pause()
{
	if (m_Status != AudioPlayerStatus::Playing)
	{
		return;
	}

	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.PauseAudio(soloudEngine, m_Handle);

	m_Status = AudioPlayerStatus::Paused;
}

void AudioPlayer::Stop()
{
	if (m_Status == AudioPlayerStatus::Stopped)
	{
		return;
	}

	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.StopAudio(soloudEngine, m_Handle);

	m_Status = AudioPlayerStatus::Stopped;

	m_Handle = -1;

	m_Audio->RemovePlayer(this);
}

f32 AudioPlayer::GetPlayerVolume() const
{
	return m_Volume;
}

void AudioPlayer::SetPlayerVolume(const f32 volume)
{
	m_Volume = volume < 0.0f ? 0.0f : volume;

	if (m_Status == AudioPlayerStatus::Stopped)
	{
		return;
	}

	UpdateCurrentAudioVolume();
}

f32 AudioPlayer::GetEffectiveVolume() const
{
	return m_Volume * m_Audio->GetVolume();
}

bool AudioPlayer::GetLoop() const
{
	return m_Loop;
}

void AudioPlayer::SetLoop(const bool loop)
{
	m_Loop = loop;

	if (m_Status == AudioPlayerStatus::Stopped)
	{
		return;
	}

	UpdateCurrentAudioLoop();
}

void AudioPlayer::OnUpdate(f32 deltaTime)
{
	if (m_Handle == -1)
	{
		return;
	}

	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();
	if (!audioBackend.IsValidAudioHandle(soloudEngine, m_Handle))
	{
		m_Status = AudioPlayerStatus::Stopped;

		m_Handle = -1;

		m_Audio->RemovePlayer(this);
	}
}

void AudioPlayer::UpdateCurrentAudioVolume() const
{
	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.SetAudioVolume(soloudEngine, m_Handle, GetEffectiveVolume());
}

void AudioPlayer::UpdateCurrentAudioLoop() const
{
	const AssetManager& assetManager = AssetManager::Get();
	SoLoud::Soloud* soloudEngine = assetManager.m_SoloudEngine;

	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.SetAudioLoop(soloudEngine, m_Handle, m_Loop);
}
