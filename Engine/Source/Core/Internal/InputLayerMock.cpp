#ifdef TESTING

#include <Core/Internal/InputLayer.h>

using namespace TGL;

// Mock variables

MouseMode g_MouseMode = MouseMode::Normal;

glm::ivec2 g_MousePosition = {0, 0};

// NOLINTBEGIN(CppParameterNeverUsed)

void InputLayer::BindKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32)) {}

void InputLayer::BindMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32)) {}

void InputLayer::BindMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputLayer::BindMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64)) {}

void InputLayer::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode)
{
	g_MouseMode = mode;
}

void InputLayer::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	g_MousePosition = position;
}

glm::ivec2 InputLayer::GetMousePosition(GLFWwindow* windowPtr)
{
	return g_MousePosition;
}

void InputLayer::PollEvents() {}

// NOLINTEND(CppParameterNeverUsed)

#endif
