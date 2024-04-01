#pragma once

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        static inline float s_TotalTime = 0.0f;
        static inline float s_DeltaTime = 0.0f;

        static inline unsigned int s_TotalFrameCount = 0;
        static inline unsigned int s_SecondFrameCount = 0;
        static inline unsigned int s_FrameRate = 1;

        static inline float s_NextSecond = 1.0f;
        static inline bool s_IsNewSecond = false;

    public:
        Clock() = delete;
        ~Clock() = delete;

    private:
        static float Update();

    public:
        static float GetTotalTime();
        static float GetDeltaTime();

        static unsigned int GetFrameCount();
        static unsigned int GetFrameRate();

        static bool IsNewSecond();
    };
}
