#include "Clock.h"

#include "GLFW/glfw3.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Services;

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
    m_FrameCount++;

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

    return s_Instance->m_FrameCount;
}
