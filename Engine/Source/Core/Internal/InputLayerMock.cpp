#include "Core/Services/InputSystem.h"
#ifdef TESTING

#include "Core/Services/Window.h"
#include <Core/Internal/InputLayer.h>

using namespace TGL;

// NOLINTBEGIN(CppParameterNeverUsed)

void InputLayer::SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*))
{
}

void InputLayer::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void InputLayer::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void InputLayer::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

void InputLayer::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

void InputLayer::SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32)) {}

void InputLayer::SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32)) {}

void InputLayer::SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputLayer::SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputLayer::CloseWindow(GLFWwindow* windowPtr)
{
	Window::CloseCallback(windowPtr);
}

void InputLayer::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title) {}

void InputLayer::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	Window::PositionCallback(windowPtr, position.x, position.y);
}

void InputLayer::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
	Window::SizeCallback(windowPtr, resolution.x, resolution.y);
}

void InputLayer::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
	Window::FullscreenCallback(fullscreen);
}

void InputLayer::MaximizeWindow(GLFWwindow* windowPtr)
{
	Window::MaximizeCallback(windowPtr, 1);
}

void InputLayer::MinimizeWindow(GLFWwindow* windowPtr)
{
	Window::MinimizeCallback(windowPtr, 1);
}

void InputLayer::RestoreWindow(GLFWwindow* windowPtr)
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

void InputLayer::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode) {}

glm::ivec2 InputLayer::GetMousePosition(GLFWwindow* windowPtr)
{
	return {0, 0}; // Only used during initialization
}

void InputLayer::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	InputSystem::MousePositionCallback(windowPtr, position.x, position.y);
}

void InputLayer::PollEvents() {}

// NOLINTEND(CppParameterNeverUsed)

#endif
