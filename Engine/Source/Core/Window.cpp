#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Entities/Camera.h"

#include "Exceptions/Core/FailedToInitializeEngineException.hpp"
#include <format>
#include <stdexcept>
#include <utility>

using namespace TGL;
using namespace TGL;

constexpr int minimun_window_resolution = 400;

Window::Window(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
    : m_Title(std::move(title)), m_Position(position), m_Resolution(resolution), m_AspectRatio(static_cast<float>(resolution.x) / static_cast<float>(resolution.y)), m_Fullscreen(fullscreen), m_Vsync(vsync)
{
    s_Instance = this;
}

bool Window::IsFullscreen()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_Fullscreen;
}

void Window::SetFullscreen(const bool fullscreen)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    if (fullscreen == s_Instance->m_Fullscreen) return;

    s_Instance->m_Fullscreen = fullscreen;

    glfwSetWindowMonitor(
        s_Instance->m_WindowPtr,
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        s_Instance->m_Position.x, s_Instance->m_Position.y,
        s_Instance->m_Resolution.x, s_Instance->m_Resolution.y,
        GLFW_DONT_CARE
    );
}

std::string Window::GetTitle()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_Title;
}

void Window::SetTitle(const std::string& title)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    s_Instance->m_Title = title;
    glfwSetWindowTitle(s_Instance->m_WindowPtr, s_Instance->m_Title.c_str());
}

glm::ivec2 Window::GetPosition()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_Position;
}

void Window::SetPosition(const glm::ivec2 position)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    // m_Position is updated in the callback
    glfwSetWindowPos(s_Instance->m_WindowPtr, position.x, position.y);
}

glm::uvec2 Window::GetResolution()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    if (resolution.x == 0 || resolution.y == 0)
    {
        throw std::invalid_argument("The resolution must be greater than 0");
    }

    // m_Resolution is updated in the callback
    glfwSetWindowSize(s_Instance->m_WindowPtr, resolution.x, resolution.y);
}

float Window::GetAspectRatio()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_AspectRatio;
}

bool Window::IsVsync()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    return s_Instance->m_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::Window);

    s_Instance->m_Vsync = vsync;
    glfwSwapInterval(vsync);
}

void Window::Init()
{
    m_WindowPtr = glfwCreateWindow(m_Resolution.x, m_Resolution.y, m_Title.c_str(), nullptr, nullptr);

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

    for (const auto camera : Entity::FindEntitiesGlobally<Camera>())
    {
        camera->SetAspectRatio(m_AspectRatio);
    }
}

void Window::SwapBuffers() const
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
