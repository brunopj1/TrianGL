#pragma once

#include <Game/Component.h>
#include <Memory/SharedPtr.h>

namespace TGL
{
    enum class AudioPlayerStatus
    {
        Playing,
        Paused,
        Stopped
    };

    // Forward declarations
    class Audio;

    class AudioPlayer final : public Component
    {
    private:
        friend class Audio;

    private:
        SharedPtr<Audio> m_Audio;
        i32 m_Handle = -1;

    private:
        AudioPlayerStatus m_Status = AudioPlayerStatus::Stopped;

    private:
        float m_Volume = 1.0f;
        bool m_Loop = false;

    public:
        AudioPlayer(SharedPtr<Audio> audio = nullptr);
        ~AudioPlayer() override;

    protected:
        void OnUpdate(float deltaTime) override;

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
        float GetVolume() const;
        void SetVolume(float volume);

        float GetFinalVolume() const;

        bool GetLoop() const;
        void SetLoop(bool loop);

    private:
        void UpdateCurrentAudioVolume() const;
        void UpdateCurrentAudioLoop() const;
    };
}
