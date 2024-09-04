#ifndef TESTING

#include "Core/InputCodes.h"
#include "GLFW/glfw3.h"
#include "InputLayer.h"

using namespace TGL;

void InputLayer::SetWindowCloseCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*))
{
	glfwSetWindowCloseCallback(windowPtr, func);
}

void InputLayer::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
	glfwSetWindowPosCallback(windowPtr, func);
}

void InputLayer::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
	glfwSetWindowSizeCallback(windowPtr, func);
}

void InputLayer::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
	glfwSetWindowMaximizeCallback(windowPtr, func);
}

void InputLayer::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
	glfwSetWindowIconifyCallback(windowPtr, func);
}

void InputLayer::SetKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32))
{
	glfwSetKeyCallback(windowPtr, func);
}

void InputLayer::SetMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32))
{
	glfwSetMouseButtonCallback(windowPtr, func);
}

void InputLayer::SetMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetCursorPosCallback(windowPtr, func);
}

void InputLayer::SetMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetScrollCallback(windowPtr, func);
}

void InputLayer::CloseWindow(GLFWwindow* windowPtr)
{
	glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
}

void InputLayer::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title)
{
	glfwSetWindowTitle(windowPtr, title.c_str());
}

void InputLayer::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	glfwSetWindowPos(windowPtr, position.x, position.y);
}

void InputLayer::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
	glfwSetWindowSize(windowPtr, resolution.x, resolution.y);
}

void InputLayer::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
	glfwSetWindowMonitor(windowPtr, fullscreen ? glfwGetPrimaryMonitor() : nullptr, position.x, position.y, resolution.x, resolution.y, GLFW_DONT_CARE);
}

void InputLayer::MaximizeWindow(GLFWwindow* windowPtr)
{
	glfwMaximizeWindow(windowPtr);
}

void InputLayer::MinimizeWindow(GLFWwindow* windowPtr)
{
	glfwIconifyWindow(windowPtr);
}

void InputLayer::RestoreWindow(GLFWwindow* windowPtr)
{
	glfwRestoreWindow(windowPtr);
}

void InputLayer::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode)
{
	const i32 glfwMode = static_cast<i32>(mode);
	glfwSetInputMode(windowPtr, GLFW_CURSOR, glfwMode);
}

glm::ivec2 InputLayer::GetMousePosition(GLFWwindow* windowPtr)
{
	double x, y;
	glfwGetCursorPos(windowPtr, &x, &y);
	return {static_cast<i32>(x), static_cast<i32>(y)};
}

void InputLayer::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	glfwSetCursorPos(windowPtr, position.x, position.y);
}

void InputLayer::PollEvents()
{
	glfwPollEvents();
}

#endif
