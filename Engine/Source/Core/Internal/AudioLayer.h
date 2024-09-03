#pragma once

#include "Core/DataTypes.h"
#include <string>

// Forward declarations
namespace SoLoud
{
	class Soloud;
	class AudioSource;
}

namespace TGL
{
	class AudioLayer final
	{
	private:
		friend class AssetManager;
		friend class AudioPlayer;
		friend class Audio;

	public:
		AudioLayer() = delete;
		~AudioLayer() = delete;

	private:
		static SoLoud::Soloud* InitSoloud(int& errorCode);
		static void TerminateSoloud(const SoLoud::Soloud* soloudEngine);

		static void SetupSoloudSettings(SoLoud::Soloud* soloudEngine);

	private:
		static SoLoud::AudioSource* LoadAudio(const std::string& filePath, bool stream);
		static void UnloadAudio(const SoLoud::AudioSource* audioSource);

	private:
		static i32 PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource);

		static void ResumeAudio(SoLoud::Soloud* soloudEngine, i32 handle);
		static void PauseAudio(SoLoud::Soloud* soloudEngine, i32 handle);
		static void StopAudio(SoLoud::Soloud* soloudEngine, i32 handle);

		static bool IsValidAudioHandle(SoLoud::Soloud* soloudEngine, i32 handle);

	private:
		static void SetAudioVolume(SoLoud::AudioSource* audioSource, f32 volume);
		static f32 GetAudioVolume(const SoLoud::AudioSource* audioSource);

	private:
		static void SetAudioVolume(SoLoud::Soloud* soloudEngine, i32 handle, f32 volume);
		static void SetAudioLoop(SoLoud::Soloud* soloudEngine, i32 handle, bool loop);
	};

}
