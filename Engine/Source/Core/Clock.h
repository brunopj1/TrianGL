#pragma once
#include "DataTypes.h"

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        static inline float s_TotalTime = 0.0f;
        static inline float s_DeltaTime = 0.0f;

        static inline u32 s_TotalFrameCount = 0;
        static inline u32 s_SecondFrameCount = 0;
        static inline u32 s_FrameRate = 1;

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

        static u32 GetFrameCount();
        static u32 GetFrameRate();

        static bool IsNewSecond();
    };
}
