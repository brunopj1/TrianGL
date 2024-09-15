#include <fstream>
#ifdef TESTING

#include "AudioBackend.h"

using namespace TGL;

// NOLINTBEGIN(CppParameterNeverUsed)

SoLoud::Soloud* AudioBackend::InitSoloud(int& errorCode)
{
	return (SoLoud::Soloud*)0x1; // NOLINT(CppCStyleCast)
}

void AudioBackend::TerminateSoloud(const SoLoud::Soloud* soloudEngine) {}

void AudioBackend::SetupSoloudSettings(SoLoud::Soloud* soloudEngine) {}

SoLoud::AudioSource* AudioBackend::LoadAudio(const std::string& filePath, bool stream)
{
	const std::ifstream file(filePath);

	if (!file.good())
	{
		return nullptr;
	}

	return (SoLoud::AudioSource*)0x1; // NOLINT(CppCStyleCast)
}

void AudioBackend::UnloadAudio(const SoLoud::AudioSource* audioSource) {}

i32 AudioBackend::PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource)
{
	return 1;
}

void AudioBackend::ResumeAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

void AudioBackend::PauseAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

void AudioBackend::StopAudio(SoLoud::Soloud* soloudEngine, i32 handle) {}

bool AudioBackend::IsValidAudioHandle(SoLoud::Soloud* soloudEngine, i32 handle)
{
	return true;
}

void AudioBackend::SetAudioVolume(SoLoud::AudioSource* audioSource, f32 volume) {}

void AudioBackend::SetAudioVolume(SoLoud::Soloud* soloudEngine, i32 handle, f32 volume) {}

void AudioBackend::SetAudioLoop(SoLoud::Soloud* soloudEngine, i32 handle, bool loop) {}

// NOLINTEND(CppParameterNeverUsed)

#endif
