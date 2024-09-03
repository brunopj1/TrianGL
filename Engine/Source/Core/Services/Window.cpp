#include <Core/Services/Window.h>

#include <Core/Application.h>
#include <Events/WindowEvents.h>
#include "Core/Internal/RenderLayer.h"
#include <format>

#include <Implementations/Entities/Camera.h>

#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <stdexcept>
#include <utility>

using namespace TGL;
using namespace TGL;

constexpr glm::uvec2 minimum_window_resolution = {400, 400};

bool Window::IsFullscreen() const
{
    return m_Fullscreen;
}

void Window::SetFullscreen(const bool fullscreen)
{
    if (fullscreen == m_Fullscreen) return;

    m_Fullscreen = fullscreen;

    RenderLayer::SetFullscreen(m_WindowPtr, fullscreen, m_Position, m_Resolution);

    // There is no glfw callback for fullscreen, so we need to call the event manually
    FullscreenCallback(fullscreen);
}

bool Window::IsMaximized() const
{
    return RenderLayer::IsMaximized(m_WindowPtr);
}

void Window::Maximize() // NOLINT(CppMemberFunctionMayBeConst)
{
    RenderLayer::MaximizeWindow(m_WindowPtr);
}

bool Window::IsMinimized() const
{
    return RenderLayer::IsMinimized(m_WindowPtr);
}

void Window::Minimize() // NOLINT(CppMemberFunctionMayBeConst)
{
    RenderLayer::MinimizeWindow(m_WindowPtr);
}

void Window::Restore() // NOLINT(CppMemberFunctionMayBeConst)
{
    RenderLayer::RestoreWindow(m_WindowPtr);
}

std::string Window::GetTitle()
{
    return m_Title;
}

void Window::SetTitle(const std::string& title)
{
    m_Title = title;

    RenderLayer::SetWindowTitle(m_WindowPtr, m_Title);
}

glm::ivec2 Window::GetPosition() const
{
    return m_Position;
}

void Window::SetPosition(const glm::ivec2 position) // NOLINT(CppMemberFunctionMayBeConst)
{
    // m_Position is updated in the callback
    RenderLayer::SetWindowPosition(m_WindowPtr, position);
}

glm::uvec2 Window::GetResolution() const
{
    return m_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution) // NOLINT(CppMemberFunctionMayBeConst)
{
    if (resolution.x < minimum_window_resolution.x || resolution.y < minimum_window_resolution.y)
    {
        throw std::invalid_argument(std::format("The resolution must be greater than {{{}, {}}}", minimum_window_resolution.x, minimum_window_resolution.y));
    }

    // m_Resolution is updated in the callback
    
    RenderLayer::SetWindowResolution(m_WindowPtr, resolution);
}

f32 Window::GetAspectRatio() const
{
    return m_AspectRatio;
}

bool Window::IsVsync() const
{
    return m_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    m_Vsync = vsync;

    RenderLayer::SetSwapInterval(m_Vsync);
}

void Window::Close() // NOLINT(CppMemberFunctionMayBeConst)
{
    RenderLayer::CloseWindow(m_WindowPtr);
}

bool Window::ShouldClose() const
{
    return RenderLayer::ShouldCloseWindow(m_WindowPtr);
}

GLFWwindow* Window::Init(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
{
    m_Title = std::move(title);
    m_Position = position;
    m_Resolution = resolution;
    m_AspectRatio = static_cast<f32>(resolution.x) / static_cast<f32>(resolution.y);
    m_Fullscreen = false; // This is updated later
    m_Vsync = vsync;
    
    m_WindowPtr = RenderLayer::CreateGlfwWindow(m_Title, m_Resolution, minimum_window_resolution);

    if (m_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    RenderLayer::SetWindowPositionCallback(m_WindowPtr, PositionCallback);
    RenderLayer::SetWindowSizeCallback(m_WindowPtr, SizeCallback);
    RenderLayer::SetWindowMaximizeCallback(m_WindowPtr, MaximizeCallback);
    RenderLayer::SetWindowMinimizeCallback(m_WindowPtr, MinimizeCallback);

    SetPosition(m_Position);

    if (fullscreen) SetFullscreen(true);

    SetVsync(m_Vsync);

    return m_WindowPtr;
}

void Window::Terminate() const
{
    RenderLayer::DestroyGlfwWindow(m_WindowPtr);
}

GLFWwindow* Window::GetGlfwWindow() const
{
    return m_WindowPtr;
}

void Window::PositionCallback(GLFWwindow* /*windowPtr*/, i32 x, i32 y)
{
    Window& window = Get();
    
    window.m_Position = {x, y};

    for (const auto listener : WindowMovedEvent::s_Listeners)
    {
        listener->OnWindowMoved(window.m_Position);
    }
}

void Window::SizeCallback(GLFWwindow* /*windowPtr*/, i32 width, i32 height)
{
    Window& window = Get();
    
    window.m_Resolution = {width, height};
    window.m_AspectRatio = static_cast<f32>(width) / static_cast<f32>(height);

    RenderLayer::SetViewport(window.m_Resolution);
    
    for (const auto camera : Entity::FindEntitiesGlobally<Camera>())
    {
        camera->SetAspectRatio(window.m_AspectRatio);
    }

    for (const auto listener : WindowResizedEvent::s_Listeners)
    {
        listener->OnWindowResized(window.m_Resolution);
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

void Window::MaximizeCallback(GLFWwindow* /*windowPtr*/, const i32 maximized)
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

void Window::MinimizeCallback(GLFWwindow* /*windowPtr*/, const i32 minimized)
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
