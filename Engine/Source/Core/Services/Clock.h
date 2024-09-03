#pragma once

#include "Internal/Macros/ServiceMacros.h"
#include <Core/DataTypes.h>
#include <Core/Service.h>
#include <chrono>

namespace TGL
{
    class Clock : public Service<Clock> // NOLINT(CppClassCanBeFinal)
    {
    private:
        friend class Application;
        
    protected:
        f32 m_TotalTime = 0.0f;
        f32 m_DeltaTime = 0.0f;

        u32 m_TotalFrameCount = 0;
        u32 m_SecondFrameCount = 0;
        u32 m_FrameRate = 1;

        f32 m_NextSecond = 1.0f;
        bool m_IsNewSecond = false;

    protected:
        std::chrono::steady_clock::time_point m_StartTime;
        std::chrono::steady_clock::time_point m_FrameTime;

    protected:
        Clock() = default;
        SERVICE_DESTRUCTOR ~Clock() = default;

    public:
        SERVICE_API f32 GetTotalTime() const;
        SERVICE_API f32 GetDeltaTime() const;

        SERVICE_API u32 GetFrameCount() const;
        SERVICE_API u32 GetFrameRate() const;

        SERVICE_API bool IsNewSecond() const;

    protected:
        SERVICE_API void Start();

    protected:
        SERVICE_API void Update();
    };
}
