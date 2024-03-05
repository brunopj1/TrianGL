#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "EntityManager.h"
#include "Entities/Camera.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include "Util/DebugFeatures.hpp"
#include <format>
#include <stdexcept>
#include <utility>

using namespace Engine::Core;
using namespace Engine::Exceptions::Core;

constexpr int minimun_window_resolution = 400;

Window::Window(std::string title, const glm::uvec2 resolution, const bool vsync = true)
    : m_Title(std::move(title)), m_Resolution(resolution), m_AspectRatio(static_cast<float>(resolution.x) / static_cast<float>(resolution.y)), m_Vsync(vsync)
{
    s_Instance = this;
}

std::string Window::GetTitle()
{
    DEBUG_SINGLETON(s_Instance, "Window");

    return s_Instance->m_Title;
}

void Window::SetTitle(std::string title)
{
    DEBUG_SINGLETON(s_Instance, "Window");

    s_Instance->m_Title = std::move(title);
    glfwSetWindowTitle(s_Instance->m_WindowPtr, s_Instance->m_Title.c_str());
}

bool Window::IsVsync()
{
    DEBUG_SINGLETON(s_Instance, "Window");

    return s_Instance->m_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    DEBUG_SINGLETON(s_Instance, "Window");

    s_Instance->m_Vsync = vsync;
    glfwSwapInterval(vsync);
}

glm::uvec2 Window::GetResolution()
{
    DEBUG_SINGLETON(s_Instance, "Window");

    return s_Instance->m_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    DEBUG_SINGLETON(s_Instance, "Window");

    if (resolution.x == 0 || resolution.y == 0)
    {
        throw std::invalid_argument(std::format("The resolution must be greater than {}", minimun_window_resolution));
    }

    glfwSetWindowSize(s_Instance->m_WindowPtr, resolution.x, resolution.y);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
}

float Window::GetAspectRatio()
{
    DEBUG_SINGLETON(s_Instance, "Window");

    return s_Instance->m_AspectRatio;
}

void Window::Init()
{
    m_WindowPtr = glfwCreateWindow(m_Resolution.x, m_Resolution.y, m_Title.c_str(), nullptr, nullptr);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

    if (m_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    glfwSetWindowSizeLimits(m_WindowPtr, minimun_window_resolution, minimun_window_resolution, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowPos(m_WindowPtr, 50, 50);

    glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* _, const int width, const int height)
    {
        s_Instance->ResizeCallback(width, height);
    });

    glfwMakeContextCurrent(m_WindowPtr);

    SetVsync(m_Vsync);
}

void Window::Terminate() const
{
    glfwDestroyWindow(m_WindowPtr);
    glfwTerminate();
}

void Window::ResizeCallback(int width, int height)
{
    m_Resolution = {width, height};
    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glViewport(0, 0, width, height);

    for (const auto camera : EntityManager::FindEntities<Entities::Camera>())
    {
        camera->SetAspectRatio(m_AspectRatio);
    }
}

void Window::UpdateBuffers() const
{
    glfwSwapBuffers(m_WindowPtr);
}

// ReSharper disable once CppMemberFunctionMayBeStatic

void Window::PollEvents() const
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_WindowPtr);
}

GLFWwindow* Window::GetGlfwWindow() const
{
    return m_WindowPtr;
}
