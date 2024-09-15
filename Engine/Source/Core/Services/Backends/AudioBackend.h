#pragma once

#include "Core/DataTypes.h"
#include "Core/Service.h"
#include "Internal/Macros/TestMacros.h"
#include <string>

// Forward declarations
namespace SoLoud
{
	class Soloud;
	class AudioSource;
}

namespace TGL
{
	class AudioBackend : public Service<AudioBackend> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class ServiceCollection;
		friend struct ServiceDeleter<AudioBackend>;

		friend class AssetManager;
		friend class AudioPlayer;
		friend class Audio;

	protected:
		AudioBackend() = default;
		~AudioBackend() = default;

	protected:
		MOCKABLE_METHOD SoLoud::Soloud* InitSoloud(int& errorCode);
		MOCKABLE_METHOD void TerminateSoloud(const SoLoud::Soloud* soloudEngine);

		MOCKABLE_METHOD void SetupSoloudSettings(SoLoud::Soloud* soloudEngine);

	protected:
		MOCKABLE_METHOD SoLoud::AudioSource* LoadAudio(const std::string& filePath, bool stream);
		MOCKABLE_METHOD void UnloadAudio(const SoLoud::AudioSource* audioSource);

	protected:
		MOCKABLE_METHOD i32 PlayAudio(SoLoud::Soloud* soloudEngine, SoLoud::AudioSource* audioSource);

		MOCKABLE_METHOD void ResumeAudio(SoLoud::Soloud* soloudEngine, i32 handle);
		MOCKABLE_METHOD void PauseAudio(SoLoud::Soloud* soloudEngine, i32 handle);
		MOCKABLE_METHOD void StopAudio(SoLoud::Soloud* soloudEngine, i32 handle);

		MOCKABLE_METHOD bool IsValidAudioHandle(SoLoud::Soloud* soloudEngine, i32 handle);

	protected:
		MOCKABLE_METHOD void SetAudioVolume(SoLoud::AudioSource* audioSource, f32 volume);

	protected:
		MOCKABLE_METHOD void SetAudioVolume(SoLoud::Soloud* soloudEngine, i32 handle, f32 volume);
		MOCKABLE_METHOD void SetAudioLoop(SoLoud::Soloud* soloudEngine, i32 handle, bool loop);
	};

}
