#include "Core/Internal/InputLayer.h"
#include "Core/Internal/RenderLayer.h"
#include <Core/Services/InputSystem.h>

#ifdef IMGUI
#include <imgui_impl_glfw.h>
#endif

using namespace TGL;

bool InputSystem::IsKeyDown(const KeyCode key) const
{
	return m_KeysDown.contains(key);
}

bool InputSystem::WasKeyPressed(const KeyCode key) const
{
	return m_KeysPressedThisFrame.contains(key);
}

bool InputSystem::WasKeyRepeated(const KeyCode key) const
{
	return m_KeysRepeatedThisFrame.contains(key);
}

bool InputSystem::WasKeyReleased(const KeyCode key) const
{
	return m_KeysReleasedThisFrame.contains(key);
}

bool InputSystem::IsMouseButtonDown(const MouseButton button) const
{
	return m_MouseButtonsDown.contains(button);
}

bool InputSystem::WasMouseButtonPressed(const MouseButton button) const
{
	return m_MouseButtonsPressedThisFrame.contains(button);
}

bool InputSystem::WasMouseButtonReleased(const MouseButton button) const
{
	return m_MouseButtonsReleasedThisFrame.contains(button);
}

glm::ivec2 InputSystem::GetMousePosition() const
{
	return m_MousePosition;
}

glm::ivec2 InputSystem::GetMouseDelta() const
{
	return m_MouseDelta;
}

void InputSystem::SetMousePosition(const glm::ivec2 position)
{
	InputLayer::SetMousePosition(m_WindowPtr, position);
	m_MousePosition = position;
}

i32 InputSystem::GetMouseScroll() const
{
	return m_MouseScroll;
}

MouseMode InputSystem::GetMouseMode() const
{
	return m_MouseMode;
}

void InputSystem::SetMouseMode(const MouseMode mode)
{
	InputLayer::SetMouseInputMode(m_WindowPtr, mode);
	m_MouseMode = mode;
}

void InputSystem::Init(GLFWwindow* windowPtr)
{
	m_WindowPtr = windowPtr;

	m_MousePosition = InputLayer::GetMousePosition(m_WindowPtr);
	m_LastMousePosition = m_MousePosition;

	InputLayer::SetKeyboardCallback(windowPtr, KeyboardCallback);
	InputLayer::SetMouseButtonCallback(windowPtr, MouseButtonCallback);
	InputLayer::SetMousePositionCallback(windowPtr, MousePositionCallback);
	InputLayer::SetMouseScrollCallback(windowPtr, MouseScrollCallback);
}

void InputSystem::OnEndOfFrame()
{
	m_KeysPressedThisFrame.clear();
	m_KeysRepeatedThisFrame.clear();
	m_KeysReleasedThisFrame.clear();

	m_MouseButtonsPressedThisFrame.clear();
	m_MouseButtonsReleasedThisFrame.clear();

	m_LastMousePosition = m_MousePosition;
	m_MouseDelta = {0, 0};
	m_MouseScroll = 0;
}

void InputSystem::PollEvents() // NOLINT(CppMemberFunctionMayBeStatic)
{
	InputLayer::PollEvents();
}

void InputSystem::KeyboardCallback(GLFWwindow* /*windowPtr*/, const i32 key, const i32 /*scancode*/, const i32 action, const i32 /*mods*/)
{
	InputSystem& inputSystem = InputSystem::Get(); // NOLINT(CppRedundantQualifier)

#ifdef IMGUI
	ImGui_ImplGlfw_KeyCallback(inputSystem.m_WindowPtr, key, 0, action, 0);
#endif

	const KeyCode keyCode = static_cast<KeyCode>(key);
	const InputAction actionCode = static_cast<InputAction>(action);

	switch (actionCode)
	{
		case InputAction::Press:
			inputSystem.m_KeysPressedThisFrame.insert(keyCode);
			inputSystem.m_KeysDown.insert(keyCode);
			break;
		case InputAction::Repeat:
			inputSystem.m_KeysRepeatedThisFrame.insert(keyCode);
			break;
		case InputAction::Release:
			inputSystem.m_KeysReleasedThisFrame.insert(keyCode);
			inputSystem.m_KeysDown.erase(keyCode);
			break;
	}
}

void InputSystem::MouseButtonCallback(GLFWwindow* /*windowPtr*/, const i32 button, const i32 action, const i32 mods) // NOLINT(CppParameterNeverUsed)
{
	InputSystem& inputSystem = InputSystem::Get(); // NOLINT(CppRedundantQualifier)

#ifdef IMGUI
	ImGui_ImplGlfw_MouseButtonCallback(inputSystem.m_WindowPtr, button, action, mods);
#endif

	const MouseButton mouseButton = static_cast<MouseButton>(button);
	const InputAction actionCode = static_cast<InputAction>(action);

	switch (actionCode)
	{
		case InputAction::Press:
			inputSystem.m_MouseButtonsPressedThisFrame.insert(mouseButton);
			inputSystem.m_MouseButtonsDown.insert(mouseButton);
			break;
		case InputAction::Repeat:
			break;
		case InputAction::Release:
			inputSystem.m_MouseButtonsReleasedThisFrame.insert(mouseButton);
			inputSystem.m_MouseButtonsDown.erase(mouseButton);
			break;
	}
}

void InputSystem::MousePositionCallback(GLFWwindow* /*windowPtr*/, const f64 x, const f64 y)
{
	InputSystem& inputSystem = InputSystem::Get(); // NOLINT(CppRedundantQualifier)

#ifdef IMGUI
	ImGui_ImplGlfw_CursorPosCallback(inputSystem.m_WindowPtr, x, y);
#endif

	inputSystem.m_MousePosition = {static_cast<i32>(x), static_cast<i32>(y)};
	inputSystem.m_MouseDelta = inputSystem.m_MousePosition - inputSystem.m_LastMousePosition;
}

void InputSystem::MouseScrollCallback(GLFWwindow* /*windowPtr*/, const f64 x, const f64 y) // NOLINT(CppParameterNeverUsed)
{
	InputSystem& inputSystem = InputSystem::Get(); // NOLINT(CppRedundantQualifier)

#ifdef IMGUI
	ImGui_ImplGlfw_ScrollCallback(inputSystem.m_WindowPtr, x, y);
#endif

	inputSystem.m_MouseScroll = static_cast<i32>(y);
}
