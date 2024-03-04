#include "InputSystem.h"

#include "GLFW/glfw3.h"
#include <iostream>

using namespace Engine::Core;

InputSystem::InputSystem()
{
    s_Instance = this;
}

InputSystem::~InputSystem()
{
    s_Instance = nullptr;
}

InputSystem* InputSystem::GetInstance()
{
    return s_Instance;
}

bool InputSystem::IsKeyDown(const KeyCode key) const
{
    return m_KeysDown.contains(key);
}

bool InputSystem::WasKeyPressed(const KeyCode key) const
{
    return m_KeysPressedThisFrame.contains(key);
}

bool InputSystem::WasKeyRepeated(KeyCode key) const
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
    glfwSetCursorPos(m_WindowPtr, position.x, position.y);
    m_MousePosition = position;
}

int InputSystem::GetMouseScroll() const
{
    return m_MouseScroll;
}

MouseMode InputSystem::GetMouseMode() const
{
    return m_MouseMode;
}

void InputSystem::SetMouseMode(MouseMode mode)
{
    const int glfwMode = static_cast<int>(mode);
    glfwSetInputMode(m_WindowPtr, GLFW_CURSOR, glfwMode);
    m_MouseMode = mode;
}

void InputSystem::Init(GLFWwindow* windowPtr)
{
    m_WindowPtr = windowPtr;

    double x, y;
    glfwGetCursorPos(m_WindowPtr, &x, &y);
    m_MousePosition = {static_cast<int>(x), static_cast<int>(y)};

    // ReSharper disable CppParameterNeverUsed
    glfwSetKeyCallback(windowPtr, [](GLFWwindow* window, const int key, int scancode, const int action, const int mods)
    {
        InputSystem* inputSystem = GetInstance();
        inputSystem->KeyboardCallback(key, action, mods);
    });

    glfwSetMouseButtonCallback(windowPtr, [](GLFWwindow* window, const int button, const int action, const int mods)
    {
        InputSystem* inputSystem = GetInstance();
        inputSystem->MouseButtonCallback(button, action, mods);
    });

    glfwSetCursorPosCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        InputSystem* inputSystem = GetInstance();
        inputSystem->MousePositionCallback(x, y);
    });

    glfwSetScrollCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        InputSystem* inputSystem = GetInstance();
        inputSystem->MouseScrollCallback(x, y);
    });
    // ReSharper restore CppParameterNeverUsed
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

void InputSystem::KeyboardCallback(const int key, const int action, const int mods)
{
    const KeyCode keyCode = static_cast<KeyCode>(key);

    switch (action)
    {
        case GLFW_PRESS:
            m_KeysPressedThisFrame.insert(keyCode);
            m_KeysDown.insert(keyCode);
            break;
        case GLFW_REPEAT:
            m_KeysRepeatedThisFrame.insert(keyCode);
            break;
        case GLFW_RELEASE:
            m_KeysReleasedThisFrame.insert(keyCode);
            m_KeysDown.erase(keyCode);
            break;
        default:
            break;
    }
}

void InputSystem::MouseButtonCallback(const int button, const int action, const int mods)
{
    const MouseButton mouseButton = static_cast<MouseButton>(button);

    switch (action)
    {
        case GLFW_PRESS:
            m_MouseButtonsPressedThisFrame.insert(mouseButton);
            m_MouseButtonsDown.insert(mouseButton);
            break;
        case GLFW_RELEASE:
            m_MouseButtonsReleasedThisFrame.insert(mouseButton);
            m_MouseButtonsDown.erase(mouseButton);
            break;
        default:
            break;
    }
}

void InputSystem::MousePositionCallback(const double x, const double y)
{
    m_MousePosition = {static_cast<int>(x), static_cast<int>(y)};
    m_MouseDelta = m_MousePosition - m_LastMousePosition;
}

// ReSharper disable once CppParameterNeverUsed
void InputSystem::MouseScrollCallback(const double x, const double y)
{
    m_MouseScroll = static_cast<int>(y);
}
