#pragma once
#include "Game/Component.h"
#include <memory>

namespace TGL
{
    enum class AudioPlayerStatus
    {
        Playing,
        Paused,
        Stopped
    };

    // Forward declarations
    class Sound;

    class AudioPlayer final : public Component
    {
    private:
        friend class Sound;

    private:
        std::shared_ptr<Sound> m_Sound;
        int m_Handle = -1;

    private:
        AudioPlayerStatus m_Status = AudioPlayerStatus::Stopped;

    private:
        float m_Volume = 1.0f;
        bool m_Loop = false;

    public:
        AudioPlayer(std::shared_ptr<Sound> sound = nullptr);
        ~AudioPlayer() override;

    protected:
        void OnUpdate(float deltaTime) override;

    public:
        std::shared_ptr<Sound> GetSound() const;
        void SetSound(std::shared_ptr<Sound> sound);

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
        void UpdateCurrentSoundVolume() const;
        void UpdateCurrentSoundLoop() const;
    };
}
