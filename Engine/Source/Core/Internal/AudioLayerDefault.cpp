#ifndef TESTING

#include "AudioLayer.h"

#include "soloud.h"
#include "soloud_wavstream.h"
#include "soloud_wav.h"

using namespace TGL;

SoLoud::Soloud* AudioLayer::InitSoloud(int& errorCode)
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

void AudioLayer::TerminateSoloud(const SoLoud::Soloud* soloudEngine)
{
    delete soloudEngine;
}

void AudioLayer::SetupSoloudSettings(SoLoud::Soloud* soloudEngine)
{
    soloudEngine->setGlobalVolume(0.1f);
}

SoLoud::AudioSource* AudioLayer::LoadAudio(const std::string& filePath, const bool stream)
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

void AudioLayer::UnloadAudio(const SoLoud::AudioSource* audioSource)
{
    delete audioSource;
}

i32 AudioLayer::PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource)
{
    return soloudEngine->play(*audioSource);
}

void AudioLayer::ResumeAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
    soloudEngine->setPause(handle, false);
}

void AudioLayer::PauseAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
    soloudEngine->setPause(handle, true);
}

void AudioLayer::StopAudio(SoLoud::Soloud* soloudEngine, const i32 handle)
{
    soloudEngine->stop(handle);
}

bool AudioLayer::IsValidAudioHandle(SoLoud::Soloud* soloudEngine, const i32 handle)
{
    return soloudEngine->isValidVoiceHandle(handle);
}

void AudioLayer::SetAudioVolume(SoLoud::AudioSource* audioSource, const f32 volume)
{
    audioSource->setVolume(volume);
}

f32 AudioLayer::GetAudioVolume(const SoLoud::AudioSource* audioSource)
{
    return audioSource->mVolume;
}

void AudioLayer::SetAudioVolume(SoLoud::Soloud* soloudEngine, const i32 handle, const f32 volume)
{
    soloudEngine->setVolume(handle, volume);
}

void AudioLayer::SetAudioLoop(SoLoud::Soloud* soloudEngine, const i32 handle, const bool loop)
{
    soloudEngine->setLooping(handle, loop);
}

#endif
