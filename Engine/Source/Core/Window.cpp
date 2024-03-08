#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Services/EntityManager.h"
#include "Entities/Camera.h"

#include "Exceptions/Core/FailedToInitializeEngineException.hpp"
#include "Util/Macros/SingletonMacros.hpp"
#include <format>
#include <stdexcept>
#include <utility>

using namespace Engine::Core;
using namespace Engine::Exceptions::Core;

constexpr int minimun_window_resolution = 400;

Window::Window(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
    : m_Title(std::move(title)), m_Position(position), m_Resolution(resolution), m_AspectRatio(static_cast<float>(resolution.x) / static_cast<float>(resolution.y)), m_Fullscreen(fullscreen), m_Vsync(vsync)
{
    s_Instance = this;
}

bool Window::IsFullscreen()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_Fullscreen;
}

void Window::SetFullscreen(const bool fullscreen)
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    if (fullscreen == s_Instance->m_Fullscreen) return;

    s_Instance->m_Fullscreen = fullscreen;

    glfwSetWindowMonitor(
        s_Instance->m_WindowPtr,
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        s_Instance->m_Position.x, s_Instance->m_Position.y,
        s_Instance->m_Resolution.x, s_Instance->m_Resolution.y, // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
        GLFW_DONT_CARE
    );
}

std::string Window::GetTitle()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_Title;
}

void Window::SetTitle(std::string title)
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    s_Instance->m_Title = std::move(title);
    glfwSetWindowTitle(s_Instance->m_WindowPtr, s_Instance->m_Title.c_str());
}

glm::ivec2 Window::GetPosition()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_Position;
}

void Window::SetPosition(const glm::ivec2 position)
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    // m_Position is updated in the callback
    glfwSetWindowPos(s_Instance->m_WindowPtr, position.x, position.y);
}

glm::uvec2 Window::GetResolution()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    if (resolution.x == 0 || resolution.y == 0)
    {
        throw std::invalid_argument(std::format("The resolution must be greater than {}", minimun_window_resolution));
    }

    // m_Resolution is updated in the callback
    glfwSetWindowSize(s_Instance->m_WindowPtr, resolution.x, resolution.y);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
}

float Window::GetAspectRatio()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_AspectRatio;
}

bool Window::IsVsync()
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    return s_Instance->m_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    SINGLETON_CHECK_IF_INITIALIZED("Window");

    s_Instance->m_Vsync = vsync;
    glfwSwapInterval(vsync);
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

    glfwSetWindowPosCallback(m_WindowPtr, [](GLFWwindow* _, const int x, const int y)
    {
        s_Instance->PositionCallback(x, y);
    });

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

void Window::PositionCallback(int x, int y)
{
    m_Position = {x, y};
}

void Window::ResizeCallback(int width, int height)
{
    m_Resolution = {width, height};
    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glViewport(0, 0, width, height);

    for (const auto camera : Services::EntityManager::FindEntities<Entities::Camera>())
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
