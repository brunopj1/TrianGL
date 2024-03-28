#include "Window.h"

#include "Events/WindowEvents.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Implementations/Entities/Camera.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <format>
#include <stdexcept>
#include <utility>

using namespace TGL;
using namespace TGL;

constexpr int minimun_window_resolution = 400;

bool Window::IsFullscreen()
{
    return s_Fullscreen;
}

void Window::SetFullscreen(const bool fullscreen)
{
    if (fullscreen == s_Fullscreen) return;

    s_Fullscreen = fullscreen;

    glfwSetWindowMonitor(
        s_WindowPtr,
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        s_Position.x, s_Position.y,
        s_Resolution.x, s_Resolution.y,
        GLFW_DONT_CARE
    );

    FullscreenCallback(fullscreen);
}

bool Window::IsMaximized()
{
    return glfwGetWindowAttrib(s_WindowPtr, GLFW_MAXIMIZED);
}

void Window::Maximize()
{
    glfwMaximizeWindow(s_WindowPtr);
}

bool Window::IsMinimized()
{
    return glfwGetWindowAttrib(s_WindowPtr, GLFW_ICONIFIED);
}

void Window::Minimize()
{
    glfwIconifyWindow(s_WindowPtr);
}

void Window::Restore()
{
    glfwRestoreWindow(s_WindowPtr);
}

std::string Window::GetTitle()
{
    return s_Title;
}

void Window::SetTitle(const std::string& title)
{
    s_Title = title;
    glfwSetWindowTitle(s_WindowPtr, s_Title.c_str());
}

glm::ivec2 Window::GetPosition()
{
    return s_Position;
}

void Window::SetPosition(const glm::ivec2 position)
{
    // s_Position is updated in the callback
    glfwSetWindowPos(s_WindowPtr, position.x, position.y);
}

glm::uvec2 Window::GetResolution()
{
    return s_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    if (resolution.x == minimun_window_resolution || resolution.y == minimun_window_resolution)
    {
        throw std::invalid_argument(std::format("The resolution must be greater than {}", minimun_window_resolution));
    }

    // s_Resolution is updated in the callback
    glfwSetWindowSize(s_WindowPtr, resolution.x, resolution.y);
}

float Window::GetAspectRatio()
{
    return s_AspectRatio;
}

bool Window::IsVsync()
{
    return s_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    s_Vsync = vsync;
    glfwSwapInterval(vsync);
}

void Window::Init(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
{
    s_Title = std::move(title);
    s_Position = position;
    s_Resolution = resolution;
    s_AspectRatio = static_cast<float>(resolution.x) / static_cast<float>(resolution.y);
    s_Fullscreen = fullscreen;
    s_Vsync = vsync;

    s_WindowPtr = glfwCreateWindow(s_Resolution.x, s_Resolution.y, s_Title.c_str(), nullptr, nullptr);

    if (s_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    glfwSetWindowSizeLimits(s_WindowPtr, minimun_window_resolution, minimun_window_resolution, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowPos(s_WindowPtr, 50, 50);

    glfwSetWindowPosCallback(s_WindowPtr, [](GLFWwindow* _, const int x, const int y)
    {
        PositionCallback(x, y);
    });

    glfwSetWindowSizeCallback(s_WindowPtr, [](GLFWwindow* _, const int width, const int height)
    {
        SizeCallback(width, height);
    });

    glfwSetWindowMaximizeCallback(s_WindowPtr, [](GLFWwindow* _, const int maximized)
    {
        maximized ? MaximizeCallback() : RestoreCallback();
    });

    glfwSetWindowIconifyCallback(s_WindowPtr, [](GLFWwindow* _, const int minimized)
    {
        minimized ? MinimizeCallback() : RestoreCallback();
    });

    glfwMakeContextCurrent(s_WindowPtr);

    SetVsync(s_Vsync);
}

void Window::Terminate()
{
    glfwDestroyWindow(s_WindowPtr);
    glfwTerminate();
}

void Window::PositionCallback(int x, int y)
{
    s_Position = {x, y};

    for (const auto listener : WindowMovedEvent::s_Listeners)
    {
        listener->OnWindowMoved(s_Position);
    }
}

void Window::SizeCallback(int width, int height)
{
    s_Resolution = {width, height};
    s_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glViewport(0, 0, width, height);

    for (const auto camera : Entity::FindEntitiesGlobally<Camera>())
    {
        camera->SetAspectRatio(s_AspectRatio);
    }

    for (const auto listener : WindowResizedEvent::s_Listeners)
    {
        listener->OnWindowResized(s_Resolution);
    }
}

void Window::FullscreenCallback(const bool fullscreen)
{
    // The value is stored in the caller

    for (const auto listener : WindowFullscreenEvent::s_Listeners)
    {
        listener->OnWindowFullscreen(fullscreen);
    }
}

void Window::MaximizeCallback()
{
    for (const auto listener : WindowMaximizedEvent::s_Listeners)
    {
        listener->OnWindowMaximized();
    }
}

void Window::MinimizeCallback()
{
    for (const auto listener : WindowMinimizedEvent::s_Listeners)
    {
        listener->OnWindowMinimized();
    }
}

void Window::RestoreCallback()
{
    for (const auto listener : WindowRestoredEvent::s_Listeners)
    {
        listener->OnWindowRestored();
    }
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(s_WindowPtr);
}

// ReSharper disable once CppMemberFunctionMayBeStatic

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(s_WindowPtr);
}

GLFWwindow* Window::GetGlfwWindow()
{
    return s_WindowPtr;
}
