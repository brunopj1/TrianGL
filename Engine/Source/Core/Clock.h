#pragma once
#include "DataTypes.h"

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        static inline f32 s_TotalTime = 0.0f;
        static inline f32 s_DeltaTime = 0.0f;

        static inline u32 s_TotalFrameCount = 0;
        static inline u32 s_SecondFrameCount = 0;
        static inline u32 s_FrameRate = 1;

        static inline f32 s_NextSecond = 1.0f;
        static inline bool s_IsNewSecond = false;

    public:
        Clock() = delete;
        ~Clock() = delete;

    private:
        static f32 Update();

    public:
        static f32 GetTotalTime();
        static f32 GetDeltaTime();

        static u32 GetFrameCount();
        static u32 GetFrameRate();

        static bool IsNewSecond();
    };
}
