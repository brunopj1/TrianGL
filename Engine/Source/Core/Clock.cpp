#include "Clock.h"

#include "GLFW/glfw3.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace TGL;

Clock::Clock()
{
    s_Instance = this;
}

Clock::~Clock()
{
    s_Instance = nullptr;
}

float Clock::Update()
{
    const float currentTime = static_cast<float>(glfwGetTime());

    m_DeltaTime = currentTime - m_TotalTime;
    m_TotalTime = currentTime;

    m_TotalFrameCount++;
    m_SecondFrameCount++;

    if (m_TotalTime >= m_NextSecond)
    {
        m_IsNewSecond = true;
        m_NextSecond += 1.0f;

        m_FrameRate = m_SecondFrameCount;
        m_SecondFrameCount = 0;
    }
    else
    {
        m_IsNewSecond = false;
    }

    return m_DeltaTime;
}

float Clock::GetTotalTime()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_TotalTime;
}

float Clock::GetDeltaTime()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_DeltaTime;
}

unsigned Clock::GetFrameCount()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_TotalFrameCount;
}

unsigned Clock::GetFrameRate()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_FrameRate;
}

bool Clock::IsNewSecond()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_IsNewSecond;
}
