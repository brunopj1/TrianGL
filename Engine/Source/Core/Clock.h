#pragma once
#include "DataTypes.h"
#include <chrono>

namespace TGL
{
    class Clock final
    {
    private:
        friend class Application;

    private:
        static inline f32 s_TotalTime;
        static inline f32 s_DeltaTime;

        static inline u32 s_TotalFrameCount;
        static inline u32 s_SecondFrameCount;
        static inline u32 s_FrameRate;

        static inline f32 s_NextSecond;
        static inline bool s_IsNewSecond;

    private:
        static inline std::chrono::steady_clock::time_point s_StartTime;
        static inline std::chrono::steady_clock::time_point s_FrameTime;

    public:
        Clock() = delete;
        ~Clock() = delete;

    public:
        static f32 GetTotalTime();
        static f32 GetDeltaTime();

        static u32 GetFrameCount();
        static u32 GetFrameRate();

        static bool IsNewSecond();

    private:
        static void Init();
        static void Start();

    private:
        static f32 Update();
    };
}
