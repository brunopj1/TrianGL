#ifndef TESTING

#include "Core/InputCodes.h"
#include "GLFW/glfw3.h"
#include "InputLayer.h"

using namespace TGL;

void InputLayer::BindKeyboardCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32, i32))
{
	glfwSetKeyCallback(windowPtr, func);
}

void InputLayer::BindMouseButtonCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32, i32))
{
	glfwSetMouseButtonCallback(windowPtr, func);
}

void InputLayer::BindMousePositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetCursorPosCallback(windowPtr, func);
}

void InputLayer::BindMouseScrollCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, f64, f64))
{
	glfwSetScrollCallback(windowPtr, func);
}

void InputLayer::SetMouseInputMode(GLFWwindow* windowPtr, const MouseMode mode)
{
	const i32 glfwMode = static_cast<i32>(mode);
	glfwSetInputMode(windowPtr, GLFW_CURSOR, glfwMode);
}

void InputLayer::SetMousePosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	glfwSetCursorPos(windowPtr, position.x, position.y);
}

glm::ivec2 InputLayer::GetMousePosition(GLFWwindow* windowPtr)
{
	double x, y;
	glfwGetCursorPos(windowPtr, &x, &y);
	return {static_cast<i32>(x), static_cast<i32>(y)};
}

void InputLayer::PollEvents()
{
	glfwPollEvents();
}

#endif
