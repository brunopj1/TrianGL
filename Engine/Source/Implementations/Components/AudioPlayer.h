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
        std::shared_ptr<Sound> m_Sound;
        int m_Handle = -1;

    private:
        AudioPlayerStatus m_Status = AudioPlayerStatus::Stopped;

    private:
        bool m_Looping = false;

    public:
        AudioPlayer(std::shared_ptr<Sound> sound = nullptr);
        ~AudioPlayer() override = default;

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
        bool GetLooping() const;
        void SetLooping(bool looping);
    };
}
