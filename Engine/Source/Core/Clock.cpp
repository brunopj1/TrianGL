#include <Core/Clock.h>

using namespace TGL;

f32 Clock::GetTotalTime()
{
    return s_TotalTime;
}

f32 Clock::GetDeltaTime()
{
    return s_DeltaTime;
}

u32 Clock::GetFrameCount()
{
    return s_TotalFrameCount;
}

u32 Clock::GetFrameRate()
{
    return s_FrameRate;
}

bool Clock::IsNewSecond()
{
    return s_IsNewSecond;
}

void Clock::Init()
{
    s_TotalTime = 0.0f;
    s_DeltaTime = 0.0f;

    s_TotalFrameCount = 0;
    s_SecondFrameCount = 0;
    s_FrameRate = 1;

    s_NextSecond = 1.0f;
    s_IsNewSecond = false;
}

void Clock::Start()
{
    s_StartTime = s_FrameTime = std::chrono::steady_clock::now();
}

f32 Clock::Update()
{
    const auto currentTime = std::chrono::steady_clock::now();

    s_DeltaTime = std::chrono::duration<f32>(currentTime - s_FrameTime).count();
    s_TotalTime = std::chrono::duration<f32>(currentTime - s_StartTime).count();

    s_FrameTime = currentTime;

    s_TotalFrameCount++;
    s_SecondFrameCount++;

    if (s_TotalTime >= s_NextSecond)
    {
        s_IsNewSecond = true;
        s_NextSecond += 1.0f;

        s_FrameRate = s_SecondFrameCount;
        s_SecondFrameCount = 0;
    }
    else
    {
        s_IsNewSecond = false;
    }

    return s_DeltaTime;
}
