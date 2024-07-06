#include <Core/InputSystem.h>

#include <GLFW/glfw3.h>

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
    glfwSetCursorPos(s_WindowPtr, position.x, position.y);
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

void InputSystem::SetMouseMode(MouseMode mode)
{
    const i32 glfwMode = static_cast<i32>(mode);
    glfwSetInputMode(s_WindowPtr, GLFW_CURSOR, glfwMode);
    s_MouseMode = mode;
}

void InputSystem::Init(GLFWwindow* windowPtr)
{
    s_WindowPtr = windowPtr;

    double posX, posY;
    glfwGetCursorPos(s_WindowPtr, &posX, &posY);
    s_MousePosition = {static_cast<i32>(posX), static_cast<i32>(posY)};

    // ReSharper disable CppParameterNeverUsed

    glfwSetKeyCallback(windowPtr, [](GLFWwindow* window, const i32 key, i32 scancode, const i32 action, const i32 mods)
    {
        KeyboardCallback(key, action, mods);
    });

    glfwSetMouseButtonCallback(windowPtr, [](GLFWwindow* window, const i32 button, const i32 action, const i32 mods)
    {
        MouseButtonCallback(button, action, mods);
    });

    glfwSetCursorPosCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        MousePositionCallback(x, y);
    });

    glfwSetScrollCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        MouseScrollCallback(x, y);
    });

    // ReSharper restore CppParameterNeverUsed
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

void InputSystem::KeyboardCallback(const i32 key, const i32 action, const i32 /*mods*/)
{
#ifdef DEBUG
    ImGui_ImplGlfw_KeyCallback(s_WindowPtr, key, 0, action, 0);
#endif

    const KeyCode keyCode = static_cast<KeyCode>(key);

    switch (action)
    {
        case GLFW_PRESS:
            s_KeysPressedThisFrame.insert(keyCode);
            s_KeysDown.insert(keyCode);
            break;
        case GLFW_REPEAT:
            s_KeysRepeatedThisFrame.insert(keyCode);
            break;
        case GLFW_RELEASE:
            s_KeysReleasedThisFrame.insert(keyCode);
            s_KeysDown.erase(keyCode);
            break;
        default:
            break;
    }
}

void InputSystem::MouseButtonCallback(const i32 button, const i32 action, const i32 mods)
{
#ifdef DEBUG
    ImGui_ImplGlfw_MouseButtonCallback(s_WindowPtr, button, action, mods);
#endif

    const MouseButton mouseButton = static_cast<MouseButton>(button);

    switch (action)
    {
        case GLFW_PRESS:
            s_MouseButtonsPressedThisFrame.insert(mouseButton);
            s_MouseButtonsDown.insert(mouseButton);
            break;
        case GLFW_RELEASE:
            s_MouseButtonsReleasedThisFrame.insert(mouseButton);
            s_MouseButtonsDown.erase(mouseButton);
            break;
        default:
            break;
    }
}

void InputSystem::MousePositionCallback(const double x, const double y)
{
#ifdef DEBUG
    ImGui_ImplGlfw_CursorPosCallback(s_WindowPtr, x, y);
#endif

    s_MousePosition = {static_cast<i32>(x), static_cast<i32>(y)};
    s_MouseDelta = s_MousePosition - s_LastMousePosition;
}

// ReSharper disable once CppParameterNeverUsed
void InputSystem::MouseScrollCallback(const double x, const double y)
{
#ifdef DEBUG
    ImGui_ImplGlfw_ScrollCallback(s_WindowPtr, x, y);
#endif

    s_MouseScroll = static_cast<i32>(y);
}
