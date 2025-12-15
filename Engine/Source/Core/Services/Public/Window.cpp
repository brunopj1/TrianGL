#include "Core/Services/Backends/InputBackend.h"
#include "Core/Services/Backends/RenderBackend.h"
#include <Core/Application.h>
#include <Core/Services/Public/Window.h>
#include <Events/WindowEvents.h>
#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <General/Camera.h>
#include <format>
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
	if (fullscreen == m_Fullscreen)
	{
		return;
	}

	m_Fullscreen = fullscreen;

	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.SetFullscreen(m_WindowPtr, fullscreen, m_Position, m_Resolution);

	// There is no glfw callback for fullscreen, so we need to call the event manually
	FullscreenCallback(fullscreen);
}

bool Window::IsMaximized() const
{
	return m_Maximized;
}

void Window::Maximize() // NOLINT(CppMemberFunctionMayBeConst)
{
	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.MaximizeWindow(m_WindowPtr);
}

bool Window::IsMinimized() const
{
	return m_Minimized;
}

void Window::Minimize() // NOLINT(CppMemberFunctionMayBeConst)
{
	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.MinimizeWindow(m_WindowPtr);
}

void Window::Restore() // NOLINT(CppMemberFunctionMayBeConst)
{
	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.RestoreWindow(m_WindowPtr);
}

std::string Window::GetTitle()
{
	return m_Title;
}

void Window::SetTitle(const std::string& title)
{
	m_Title = title;

	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.SetWindowTitle(m_WindowPtr, m_Title);
}

glm::ivec2 Window::GetPosition() const
{
	return m_Position;
}

void Window::SetPosition(const glm::ivec2 position) // NOLINT(CppMemberFunctionMayBeConst)
{
	// m_Position is updated in the callback
	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.SetWindowPosition(m_WindowPtr, position);
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

	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.SetWindowResolution(m_WindowPtr, resolution);
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

	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetSwapInterval(m_Vsync);
}

void Window::Close() // NOLINT(CppMemberFunctionMayBeConst)
{
	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.CloseWindow(m_WindowPtr);
}

bool Window::IsClosing() const
{
	return m_Closing;
}

GLFWwindow* Window::Init(std::string title, const glm::ivec2 position, const glm::uvec2 resolution, const bool fullscreen, const bool vsync)
{
	m_Title = std::move(title);
	m_Position = position;
	m_Resolution = resolution;
	m_AspectRatio = static_cast<f32>(resolution.x) / static_cast<f32>(resolution.y);
	m_Fullscreen = false; // This is updated later
	m_Vsync = vsync;

	RenderBackend& renderBackend = RenderBackend::Get();
	m_WindowPtr = renderBackend.CreateGlfwWindow(m_Title, m_Resolution, minimum_window_resolution);

	if (m_WindowPtr == nullptr)
	{
		throw FailedToInitializeEngineException("Failed to create GLFW window");
	}

	InputBackend& inputBackend = InputBackend::Get();
	inputBackend.SetWindowCloseCallback(m_WindowPtr, CloseCallback);
	inputBackend.SetWindowPositionCallback(m_WindowPtr, PositionCallback);
	inputBackend.SetWindowSizeCallback(m_WindowPtr, SizeCallback);
	inputBackend.SetWindowMaximizeCallback(m_WindowPtr, MaximizeCallback);
	inputBackend.SetWindowMinimizeCallback(m_WindowPtr, MinimizeCallback);

	// SetPosition(m_Position);

	if (fullscreen)
	{
		SetFullscreen(true);
	}

	SetVsync(m_Vsync);

	return m_WindowPtr;
}

void Window::Terminate() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.DestroyGlfwWindow(m_WindowPtr);
}

GLFWwindow* Window::GetGlfwWindow() const
{
	return m_WindowPtr;
}
void Window::CloseCallback(GLFWwindow* /*windowPtr*/)
{
	Window& window = Get();
	window.m_Closing = true;
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

	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetViewport(window.m_Resolution);

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
	Window& window = Get();
	window.m_Maximized = maximized;

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
	Window& window = Get();
	window.m_Minimized = minimized;

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
