#ifndef TESTING

#include "Core/InputCodes.h"
#include "GLFW/glfw3.h"
#include "InputBackend.h"

using namespace TGL;

// NOLINTBEGIN(CppMemberFunctionMayBeStatic)

void InputBackend::SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*))
{
	glfwSetWindowCloseCallback(windowPtr, func);
}

void InputBackend::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
	glfwSetWindowPosCallback(windowPtr, func);
}

void InputBackend::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
	glfwSetWindowSizeCallback(windowPtr, func);
}

void InputBackend::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
	glfwSetWindowMaximizeCallback(windowPtr, func);
}

void InputBackend::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
	glfwSetWindowIconifyCallback(windowPtr, func);
}

void InputBackend::SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32))
{
	glfwSetKeyCallback(windowPtr, func);
}

void InputBackend::SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32))
{
	glfwSetMouseButtonCallback(windowPtr, func);
}

void InputBackend::SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetCursorPosCallback(windowPtr, func);
}

void InputBackend::SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetScrollCallback(windowPtr, func);
}

void InputBackend::CloseWindow(GLFWwindow* windowPtr)
{
	glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
}

void InputBackend::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title)
{
	glfwSetWindowTitle(windowPtr, title.c_str());
}

void InputBackend::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	glfwSetWindowPos(windowPtr, position.x, position.y);
}

void InputBackend::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
	glfwSetWindowSize(windowPtr, resolution.x, resolution.y);
}

void InputBackend::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
	glfwSetWindowMonitor(windowPtr, fullscreen ? glfwGetPrimaryMonitor() : nullptr, position.x, position.y, resolution.x, resolution.y, GLFW_DONT_CARE);
}

void InputBackend::MaximizeWindow(GLFWwindow* windowPtr)
{
	glfwMaximizeWindow(windowPtr);
}

void InputBackend::MinimizeWindow(GLFWwindow* windowPtr)
{
	glfwIconifyWindow(windowPtr);
}

void InputBackend::RestoreWindow(GLFWwindow* windowPtr)
{
	glfwRestoreWindow(windowPtr);
}

void InputBackend::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode)
{
	const i32 glfwMode = static_cast<i32>(mode);
	glfwSetInputMode(windowPtr, GLFW_CURSOR, glfwMode);
}

glm::ivec2 InputBackend::GetMousePosition(GLFWwindow* windowPtr)
{
	f64 x, y;
	glfwGetCursorPos(windowPtr, &x, &y);
	return {static_cast<i32>(x), static_cast<i32>(y)};
}

void InputBackend::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	glfwSetCursorPos(windowPtr, position.x, position.y);
}

void InputBackend::PollEvents()
{
	glfwPollEvents();
}

// NOLINTEND(CppMemberFunctionMayBeStatic)

#endif
