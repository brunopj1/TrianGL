#ifndef TESTING

#include "AudioBackend.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

using namespace TGL;

SoLoud::Soloud* AudioBackend::InitSoloud(int& errorCode)
{
	SoLoud::Soloud* soloudEngine = new SoLoud::Soloud();

	const SoLoud::result result = soloudEngine->init();

	if (result != SoLoud::SO_NO_ERROR)
	{
		errorCode = static_cast<int>(result);
		delete soloudEngine;
		return nullptr;
	}

	return soloudEngine;
}

void AudioBackend::TerminateSoloud(const SoLoud::Soloud* soloudEngine)
{
	delete soloudEngine;
}

void AudioBackend::SetupSoloudSettings(SoLoud::Soloud* soloudEngine)
{
	soloudEngine->setGlobalVolume(0.1f);
}

SoLoud::AudioSource* AudioBackend::LoadAudio(const std::string& filePath, const bool stream)
{
	SoLoud::result result;
	SoLoud::AudioSource* audioSource;

	if (stream)
	{
		SoLoud::WavStream* soloudAudio = new SoLoud::WavStream();
		result = soloudAudio->load(filePath.c_str());
		audioSource = soloudAudio;
	}
	else
	{
		SoLoud::Wav* soloudAudio = new SoLoud::Wav();
		result = soloudAudio->load(filePath.c_str());
		audioSource = soloudAudio;
	}

	if (result != SoLoud::SO_NO_ERROR)
	{
		delete audioSource;
		audioSource = nullptr;
	}

	return audioSource;
}

void AudioBackend::UnloadAudio(const SoLoud::AudioSource* audioSource)
{
	delete audioSource;
}

i32 AudioBackend::PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource)
{
	return soloudEngine->play(*audioSource);
}

void AudioBackend::ResumeAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
	soloudEngine->setPause(handle, false);
}

void AudioBackend::PauseAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
	soloudEngine->setPause(handle, true);
}

void AudioBackend::StopAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
	soloudEngine->stop(handle);
}

bool AudioBackend::IsValidAudioHandle(SoLoud::Soloud* soloudEngine, const i32 handle)
{
	return soloudEngine->isValidVoiceHandle(handle);
}

void AudioBackend::SetAudioVolume(SoLoud::AudioSource* audioSource, const f32 volume)
{
	audioSource->setVolume(volume);
}

f32 AudioBackend::GetAudioVolume(const SoLoud::AudioSource* audioSource)
{
	return audioSource->mVolume;
}

void AudioBackend::SetAudioVolume(SoLoud::Soloud* soloudEngine, const i32 handle, const f32 volume)
{
	soloudEngine->setVolume(handle, volume);
}

void AudioBackend::SetAudioLoop(SoLoud::Soloud* soloudEngine, const i32 handle, const bool loop)
{
	soloudEngine->setLooping(handle, loop);
}

#endif
