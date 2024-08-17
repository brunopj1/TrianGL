#include <Core/Window.h>

#include <Core/Application.h>
#include <Events/WindowEvents.h>
#include "Internal/RenderLayer.h"
#include <format>

#include <Implementations/Entities/Camera.h>

#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <stdexcept>
#include <utility>

using namespace TGL;
using namespace TGL;

constexpr glm::uvec2 minimum_window_resolution = {400, 400};

bool Window::IsFullscreen()
{
    return s_Fullscreen;
}

void Window::SetFullscreen(const bool fullscreen)
{
    ASSERT_APPLICATION_AVAILABILITY();

    if (fullscreen == s_Fullscreen) return;

    s_Fullscreen = fullscreen;

    RenderLayer::SetFullscreen(s_WindowPtr, fullscreen, s_Position, s_Resolution);

    // There is no glfw callback for fullscreen, so we need to call the event manually
    FullscreenCallback(fullscreen);
}

bool Window::IsMaximized()
{
    ASSERT_APPLICATION_AVAILABILITY();

    return RenderLayer::IsMaximized(s_WindowPtr);
}

void Window::Maximize()
{
    ASSERT_APPLICATION_AVAILABILITY();

    RenderLayer::MaximizeWindow(s_WindowPtr);
}

bool Window::IsMinimized()
{
    ASSERT_APPLICATION_AVAILABILITY();

    return RenderLayer::IsMinimized(s_WindowPtr);
}

void Window::Minimize()
{
    ASSERT_APPLICATION_AVAILABILITY();

    RenderLayer::MinimizeWindow(s_WindowPtr);
}

void Window::Restore()
{
    ASSERT_APPLICATION_AVAILABILITY();

    RenderLayer::RestoreWindow(s_WindowPtr);
}

std::string Window::GetTitle()
{
    return s_Title;
}

void Window::SetTitle(const std::string& title)
{
    ASSERT_APPLICATION_AVAILABILITY();

    s_Title = title;

    RenderLayer::SetWindowTitle(s_WindowPtr, s_Title);
}

glm::ivec2 Window::GetPosition()
{
    return s_Position;
}

void Window::SetPosition(const glm::ivec2 position)
{
    ASSERT_APPLICATION_AVAILABILITY();

    // s_Position is updated in the callback
    RenderLayer::SetWindowPosition(s_WindowPtr, position);
}

glm::uvec2 Window::GetResolution()
{
    return s_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    ASSERT_APPLICATION_AVAILABILITY();

    if (resolution.x < minimum_window_resolution.x || resolution.y < minimum_window_resolution.y)
    {
        throw std::invalid_argument(std::format("The resolution must be greater than {{{}, {}}}", minimum_window_resolution.x, minimum_window_resolution.y));
    }

    // s_Resolution is updated in the callback
    RenderLayer::SetWindowResolution(s_WindowPtr, resolution);
}

f32 Window::GetAspectRatio()
{
    return s_AspectRatio;
}

bool Window::IsVsync()
{
    return s_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    ASSERT_APPLICATION_AVAILABILITY();

    s_Vsync = vsync;

    RenderLayer::SetSwapInterval(s_Vsync);
}

void Window::Close()
{
    ASSERT_APPLICATION_AVAILABILITY();

    RenderLayer::CloseWindow(s_WindowPtr);
}

GLFWwindow* Window::Init(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
{
    s_Title = std::move(title);
    s_Position = position;
    s_Resolution = resolution;
    s_AspectRatio = static_cast<f32>(resolution.x) / static_cast<f32>(resolution.y);
    s_Fullscreen = false; // This is updated later
    s_Vsync = vsync;
    

    s_WindowPtr = RenderLayer::CreateWindow(s_Title, s_Resolution, minimum_window_resolution);

    if (s_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    RenderLayer::SetWindowPositionCallback(s_WindowPtr, PositionCallback);
    RenderLayer::SetWindowSizeCallback(s_WindowPtr, SizeCallback);
    RenderLayer::SetWindowMaximizeCallback(s_WindowPtr, MaximizeCallback);
    RenderLayer::SetWindowMinimizeCallback(s_WindowPtr, MinimizeCallback);

    SetPosition(s_Position);

    if (fullscreen) SetFullscreen(true);

    SetVsync(s_Vsync);

    return s_WindowPtr;
}

void Window::Terminate()
{
    RenderLayer::DestroyWindow(s_WindowPtr);
}

void Window::PositionCallback(GLFWwindow* /* windowPtr */, i32 x, i32 y)
{
    s_Position = {x, y};

    for (const auto listener : WindowMovedEvent::s_Listeners)
    {
        listener->OnWindowMoved(s_Position);
    }
}

void Window::SizeCallback(GLFWwindow* /* windowPtr */, i32 width, i32 height)
{
    s_Resolution = {width, height};
    s_AspectRatio = static_cast<f32>(width) / static_cast<f32>(height);

    RenderLayer::SetupOpenGlVersion();

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

void Window::MaximizeCallback(GLFWwindow* /* windowPtr */, const i32 maximized)
{
    if (maximized)
    {
        for (const auto listener : WindowMaximizedEvent::s_Listeners)
        {
            listener->OnWindowMaximized();
        }
    }
    else // Restored
    {
        for (const auto listener : WindowRestoredEvent::s_Listeners)
        {
            listener->OnWindowRestored();
        }
    }
}

void Window::MinimizeCallback(GLFWwindow* /* windowPtr */, const i32 minimized)
{
    if (minimized)
    {
        for (const auto listener : WindowMinimizedEvent::s_Listeners)
        {
            listener->OnWindowMinimized();
        }
    }
    else // Restored
    {
        for (const auto listener : WindowRestoredEvent::s_Listeners)
        {
            listener->OnWindowRestored();
        }
    }
}

bool Window::ShouldClose()
{
    return RenderLayer::ShouldCloseWindow(s_WindowPtr);
}

GLFWwindow* Window::GetGlfwWindow()
{
    return s_WindowPtr;
}
