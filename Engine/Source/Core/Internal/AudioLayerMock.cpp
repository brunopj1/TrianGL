#ifdef TESTING

#include "AudioLayer.h"

using namespace TGL;

// NOLINTBEGIN(CppParameterNeverUsed)

SoLoud::Soloud* AudioLayer::InitSoloud(int& errorCode)
{
	return (SoLoud::Soloud*)0x1; // NOLINT(CppCStyleCast)
}

void AudioLayer::TerminateSoloud(const SoLoud::Soloud* soloudEngine) {}

void AudioLayer::SetupSoloudSettings(SoLoud::Soloud* soloudEngine) {}

SoLoud::AudioSource* AudioLayer::LoadAudio(const std::string& filePath, bool stream)
{
	return (SoLoud::AudioSource*)0x1; // NOLINT(CppCStyleCast)
}

void AudioLayer::UnloadAudio(const SoLoud::AudioSource* audioSource) {}

i32 AudioLayer::PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource)
{
	return 1;
}

void AudioLayer::ResumeAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

void AudioLayer::PauseAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

void AudioLayer::StopAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

bool AudioLayer::IsValidAudioHandle(SoLoud::Soloud* soloudEngine, i32 handle)
{
	return true;
}

void AudioLayer::SetAudioVolume(SoLoud::AudioSource* audioSource, f32 volume) {}

f32 AudioLayer::GetAudioVolume(const SoLoud::AudioSource* audioSource)
{
	return 1.0f;
}

void AudioLayer::SetAudioVolume(SoLoud::Soloud* soloudEngine, i32 handle, f32 volume) {}

void AudioLayer::SetAudioLoop(SoLoud::Soloud* soloudEngine, i32 handle, bool loop) {}

// NOLINTEND(CppParameterNeverUsed)

#endif
