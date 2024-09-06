#include <Core/Services/Public/InputSystem.h>

#ifdef TESTING

#include <Core/Services/Backends/InputBackend.h>
#include <Core/Services/Public/Window.h>

using namespace TGL;

// NOLINTBEGIN(CppParameterNeverUsed)

void InputBackend::SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*))
{
}

void InputBackend::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void InputBackend::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void InputBackend::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

void InputBackend::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

void InputBackend::SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32)) {}

void InputBackend::SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32)) {}

void InputBackend::SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputBackend::SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputBackend::CloseWindow(GLFWwindow* windowPtr)
{
	Window::CloseCallback(windowPtr);
}

void InputBackend::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title) {}

void InputBackend::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	Window::PositionCallback(windowPtr, position.x, position.y);
}

void InputBackend::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
	Window::SizeCallback(windowPtr, resolution.x, resolution.y);
}

void InputBackend::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
	Window::FullscreenCallback(fullscreen);
}

void InputBackend::MaximizeWindow(GLFWwindow* windowPtr)
{
	Window::MaximizeCallback(windowPtr, 1);
}

void InputBackend::MinimizeWindow(GLFWwindow* windowPtr)
{
	Window::MinimizeCallback(windowPtr, 1);
}

void InputBackend::RestoreWindow(GLFWwindow* windowPtr)
{
	const Window& window = Window::Get();

	if (window.IsMaximized())
	{
		Window::MaximizeCallback(windowPtr, 0);
	}
	else if (window.IsMinimized())
	{
		Window::MinimizeCallback(windowPtr, 0);
	}
}

void InputBackend::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode) {}

glm::ivec2 InputBackend::GetMousePosition(GLFWwindow* windowPtr)
{
	return {0, 0}; // Only used during initialization
}

void InputBackend::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	InputSystem::MousePositionCallback(windowPtr, position.x, position.y);
}

void InputBackend::PollEvents() {}

// NOLINTEND(CppParameterNeverUsed)

#endif
