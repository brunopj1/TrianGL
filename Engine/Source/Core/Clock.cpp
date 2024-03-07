#include "Clock.h"

#include "GLFW/glfw3.h"

using namespace Engine::Core;

float Clock::Update()
{
    const float currentTime = static_cast<float>(glfwGetTime());

    m_DeltaTime = currentTime - m_TotalTime;
    m_TotalTime = currentTime;
    m_FrameCount++;

    return m_DeltaTime;
}

float Clock::GetTotalTime() const
{
    return m_TotalTime;
}

float Clock::GetDeltaTime() const
{
    return m_DeltaTime;
}

unsigned Clock::GetFrameCount() const
{
    return m_FrameCount;
}
