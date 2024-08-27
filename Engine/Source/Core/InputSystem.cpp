#include "Internal/InputLayer.h"
#include <Core/InputSystem.h>

#ifdef DEBUG
#include <imgui_impl_glfw.h>
#endif

using namespace TGL;

bool InputSystem::IsKeyDown(const KeyCode key)
{
    return s_KeysDown.contains(key);
}

bool InputSystem::WasKeyPressed(const KeyCode key)
{
    return s_KeysPressedThisFrame.contains(key);
}

bool InputSystem::WasKeyRepeated(const KeyCode key)
{
    return s_KeysRepeatedThisFrame.contains(key);
}

bool InputSystem::WasKeyReleased(const KeyCode key)
{
    return s_KeysReleasedThisFrame.contains(key);
}

bool InputSystem::IsMouseButtonDown(const MouseButton button)
{
    return s_MouseButtonsDown.contains(button);
}

bool InputSystem::WasMouseButtonPressed(const MouseButton button)
{
    return s_MouseButtonsPressedThisFrame.contains(button);
}

bool InputSystem::WasMouseButtonReleased(const MouseButton button)
{
    return s_MouseButtonsReleasedThisFrame.contains(button);
}

glm::ivec2 InputSystem::GetMousePosition()
{
    return s_MousePosition;
}

glm::ivec2 InputSystem::GetMouseDelta()
{
    return s_MouseDelta;
}

void InputSystem::SetMousePosition(const glm::ivec2 position)
{
    InputLayer::SetMousePosition(s_WindowPtr, position);
    s_MousePosition = position;
}

i32 InputSystem::GetMouseScroll()
{
    return s_MouseScroll;
}

MouseMode InputSystem::GetMouseMode()
{
    return s_MouseMode;
}

void InputSystem::SetMouseMode(const MouseMode mode)
{
    InputLayer::SetMouseInputMode(s_WindowPtr, mode);
    s_MouseMode = mode;
}

void InputSystem::Init(GLFWwindow* windowPtr)
{
    s_WindowPtr = windowPtr;

    s_MousePosition = InputLayer::GetMousePosition(s_WindowPtr);
    s_LastMousePosition = s_MousePosition;

    s_MouseDelta = {0, 0};
    s_MouseScroll = 0;

    s_MouseMode = MouseMode::Normal;

    InputLayer::BindKeyboardCallback(windowPtr, KeyboardCallback);
    InputLayer::BindMouseButtonCallback(windowPtr, MouseButtonCallback);
    InputLayer::BindMousePositionCallback(windowPtr, MousePositionCallback);
    InputLayer::BindMouseScrollCallback(windowPtr, MouseScrollCallback);
}

void InputSystem::Terminate()
{
    s_KeysPressedThisFrame.clear();
    s_KeysRepeatedThisFrame.clear();
    s_KeysReleasedThisFrame.clear();
    s_KeysDown.clear();

    s_MouseButtonsPressedThisFrame.clear();
    s_MouseButtonsReleasedThisFrame.clear();
    s_MouseButtonsDown.clear();
}

void InputSystem::OnEndOfFrame()
{
    s_KeysPressedThisFrame.clear();
    s_KeysRepeatedThisFrame.clear();
    s_KeysReleasedThisFrame.clear();

    s_MouseButtonsPressedThisFrame.clear();
    s_MouseButtonsReleasedThisFrame.clear();

    s_LastMousePosition = s_MousePosition;
    s_MouseDelta = {0, 0};
    s_MouseScroll = 0;
}

void InputSystem::KeyboardCallback(GLFWwindow* /*windowPtr*/, const i32 key, const i32 /*scancode*/, const i32 action, const i32 /*mods*/)
{
#ifdef DEBUG
    ImGui_ImplGlfw_KeyCallback(s_WindowPtr, key, 0, action, 0);
#endif

    const KeyCode keyCode = static_cast<KeyCode>(key);
    const InputAction actionCode = static_cast<InputAction>(action);
    
    switch (actionCode)
    {
        case InputAction::Press:
            s_KeysPressedThisFrame.insert(keyCode);
            s_KeysDown.insert(keyCode);
            break;
        case InputAction::Repeat:
            s_KeysRepeatedThisFrame.insert(keyCode);
            break;
        case InputAction::Release:
            s_KeysReleasedThisFrame.insert(keyCode);
            s_KeysDown.erase(keyCode);
            break;
    }
}

void InputSystem::MouseButtonCallback(GLFWwindow* /*windowPtr*/, const i32 button, const i32 action, const i32 mods)
{
#ifdef DEBUG
    ImGui_ImplGlfw_MouseButtonCallback(s_WindowPtr, button, action, mods);
#endif

    const MouseButton mouseButton = static_cast<MouseButton>(button);
    const InputAction actionCode = static_cast<InputAction>(action);

    switch (actionCode)
    {
        case InputAction::Press:
            s_MouseButtonsPressedThisFrame.insert(mouseButton);
            s_MouseButtonsDown.insert(mouseButton);
            break;
        case InputAction::Repeat:
            break;
        case InputAction::Release:
            s_MouseButtonsReleasedThisFrame.insert(mouseButton);
            s_MouseButtonsDown.erase(mouseButton);
            break;
    }
}

void InputSystem::MousePositionCallback(GLFWwindow* /*windowPtr*/, const f64 x, const f64 y)
{
#ifdef DEBUG
    ImGui_ImplGlfw_CursorPosCallback(s_WindowPtr, x, y);
#endif

    s_MousePosition = {static_cast<i32>(x), static_cast<i32>(y)};
    s_MouseDelta = s_MousePosition - s_LastMousePosition;
}

// ReSharper disable once CppParameterNeverUsed
void InputSystem::MouseScrollCallback(GLFWwindow* /*windowPtr*/, const f64 x, const f64 y)
{
#ifdef DEBUG
    ImGui_ImplGlfw_ScrollCallback(s_WindowPtr, x, y);
#endif

    s_MouseScroll = static_cast<i32>(y);
}
