#pragma once

#include "DataTypes.h"
#include "Service.h"
#include <chrono>

namespace TGL
{
    class Clock : public Service<Clock>
    {
    private:
        friend class Application;
        
    private:
        f32 m_TotalTime = 0.0f;
        f32 m_DeltaTime = 0.0f;

        u32 m_TotalFrameCount = 0;
        u32 m_SecondFrameCount = 0;
        u32 m_FrameRate = 1;

        f32 m_NextSecond = 1.0f;
        bool m_IsNewSecond = false;

    private:
        std::chrono::steady_clock::time_point m_StartTime;
        std::chrono::steady_clock::time_point m_FrameTime;

    private:
        Clock() = default;
        ~Clock() = default;

    public:
        f32 GetTotalTime() const;
        f32 GetDeltaTime() const;

        u32 GetFrameCount() const;
        u32 GetFrameRate() const;

        bool IsNewSecond() const;

    private:
        void Start();

    private:
        f32 Update();
    };
}
