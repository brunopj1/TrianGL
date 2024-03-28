#include "Clock.h"

#include "GLFW/glfw3.h"

using namespace TGL;

float Clock::Update()
{
    const float currentTime = static_cast<float>(glfwGetTime());

    s_DeltaTime = currentTime - s_TotalTime;
    s_TotalTime = currentTime;

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

float Clock::GetTotalTime()
{
    return s_TotalTime;
}

float Clock::GetDeltaTime()
{
    return s_DeltaTime;
}

unsigned Clock::GetFrameCount()
{
    return s_TotalFrameCount;
}

unsigned Clock::GetFrameRate()
{
    return s_FrameRate;
}

bool Clock::IsNewSecond()
{
    return s_IsNewSecond;
}
