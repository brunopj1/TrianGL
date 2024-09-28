#pragma once

#include <Game/Component.h>
#include <Memory/SharedPtr.h>

namespace TGL
{
	enum class AudioPlayerStatus : u8
	{
		Playing,
		Paused,
		Stopped
	};

	// Forward declarations
	class Audio;

	class AudioPlayer : public Component // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class Audio;

	private:
		SharedPtr<Audio> m_Audio;
		i32 m_Handle = -1;

	private:
		AudioPlayerStatus m_Status = AudioPlayerStatus::Stopped;

	private:
		f32 m_Volume = 1.0f;
		bool m_Loop = false;

	public:
		AudioPlayer(SharedPtr<Audio> audio = nullptr);
		~AudioPlayer() override;

	public:
		SharedPtr<Audio> GetAudio() const;
		void SetAudio(SharedPtr<Audio> audio);

	public:
		AudioPlayerStatus GetStatus() const;

	public:
		void Play();
		void Pause();
		void Stop();

	public:
		f32 GetPlayerVolume() const;
		void SetPlayerVolume(f32 volume);

		f32 GetEffectiveVolume() const;

		bool GetLoop() const;
		void SetLoop(bool loop);

	protected:
		void OnUpdate(f32 deltaTime) override;

	private:
		void UpdateCurrentAudioVolume() const;
		void UpdateCurrentAudioLoop() const;
	};
}
