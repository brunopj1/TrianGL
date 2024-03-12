#pragma once

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        inline static Clock* s_Instance = nullptr;

    private:
        float m_TotalTime = 0.0f;
        float m_DeltaTime = 0.0f;
        unsigned int m_FrameCount = 0;

    private:
        Clock();
        ~Clock();

    private:
        float Update();

    public:
        static float GetTotalTime();
        static float GetDeltaTime();
        static unsigned int GetFrameCount();
    };
}
