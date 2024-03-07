#pragma once

namespace Engine::Core
{
    // Forward declarations
    class Application;

    class Clock
    {
    private:
        friend class Application;

    private:
        float m_TotalTime = 0.0f;
        float m_DeltaTime = 0.0f;
        unsigned int m_FrameCount = 0;

    private:
        Clock() = default;
        ~Clock() = default;

    private:
        float Update();

    public:
        float GetTotalTime() const;
        float GetDeltaTime() const;
        unsigned int GetFrameCount() const;
    };
}
