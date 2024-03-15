#include "InputSystem.h"

#include "GLFW/glfw3.h"
#include "../Util/Macros/SingletonMacros.hpp"

#ifdef DEBUG
#include <imgui_impl_glfw.h>
#endif

using namespace TGL;

InputSystem::InputSystem()
{
    s_Instance = this;
}

InputSystem::~InputSystem()
{
    s_Instance = nullptr;
}

bool InputSystem::IsKeyDown(const KeyCode key)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_KeysDown.contains(key);
}

bool InputSystem::WasKeyPressed(const KeyCode key)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_KeysPressedThisFrame.contains(key);
}

bool InputSystem::WasKeyRepeated(const KeyCode key)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_KeysRepeatedThisFrame.contains(key);
}

bool InputSystem::WasKeyReleased(const KeyCode key)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_KeysReleasedThisFrame.contains(key);
}

bool InputSystem::IsMouseButtonDown(const MouseButton button)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseButtonsDown.contains(button);
}

bool InputSystem::WasMouseButtonPressed(const MouseButton button)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseButtonsPressedThisFrame.contains(button);
}

bool InputSystem::WasMouseButtonReleased(const MouseButton button)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseButtonsReleasedThisFrame.contains(button);
}

glm::ivec2 InputSystem::GetMousePosition()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MousePosition;
}

glm::ivec2 InputSystem::GetMouseDelta()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseDelta;
}

void InputSystem::SetMousePosition(const glm::ivec2 position)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    glfwSetCursorPos(s_Instance->m_WindowPtr, position.x, position.y);
    s_Instance->m_MousePosition = position;
}

int InputSystem::GetMouseScroll()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseScroll;
}

MouseMode InputSystem::GetMouseMode()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    return s_Instance->m_MouseMode;
}

void InputSystem::SetMouseMode(MouseMode mode)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::InputSystem);

    const int glfwMode = static_cast<int>(mode);
    glfwSetInputMode(s_Instance->m_WindowPtr, GLFW_CURSOR, glfwMode);
    s_Instance->m_MouseMode = mode;
}

void InputSystem::Init(GLFWwindow* windowPtr)
{
    m_WindowPtr = windowPtr;

    double posX, posY;
    glfwGetCursorPos(m_WindowPtr, &posX, &posY);
    m_MousePosition = {static_cast<int>(posX), static_cast<int>(posY)};

    // ReSharper disable CppParameterNeverUsed

    glfwSetKeyCallback(windowPtr, [](GLFWwindow* window, const int key, int scancode, const int action, const int mods)
    {
        s_Instance->KeyboardCallback(key, action, mods);
    });

    glfwSetMouseButtonCallback(windowPtr, [](GLFWwindow* window, const int button, const int action, const int mods)
    {
        s_Instance->MouseButtonCallback(button, action, mods);
    });

    glfwSetCursorPosCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        s_Instance->MousePositionCallback(x, y);
    });

    glfwSetScrollCallback(windowPtr, [](GLFWwindow* window, const double x, const double y)
    {
        s_Instance->MouseScrollCallback(x, y);
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

void InputSystem::KeyboardCallback(const int key, const int action, const int /*mods*/)
{
#ifdef DEBUG
    ImGui_ImplGlfw_KeyCallback(m_WindowPtr, key, 0, action, 0);
#endif

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
#ifdef DEBUG
    ImGui_ImplGlfw_MouseButtonCallback(m_WindowPtr, button, action, mods);
#endif

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
#ifdef DEBUG
    ImGui_ImplGlfw_CursorPosCallback(m_WindowPtr, x, y);
#endif

    m_MousePosition = {static_cast<int>(x), static_cast<int>(y)};
    m_MouseDelta = m_MousePosition - m_LastMousePosition;
}

// ReSharper disable once CppParameterNeverUsed
void InputSystem::MouseScrollCallback(const double x, const double y)
{
#ifdef DEBUG
    ImGui_ImplGlfw_ScrollCallback(m_WindowPtr, x, y);
#endif

    m_MouseScroll = static_cast<int>(y);
}
