#pragma once

#include "DataTypes.h"
#include "Service.h"
#include <Core/InputCodes.h>
#include <glm/vec2.hpp>
#include <unordered_set>

// TODO dont register the input if the user is interacting with ImGui
// TODO add methods to simulate input in the unit tests

// Forward declarations
// ReSharper disable once CppInconsistentNaming, IdentifierTypo
struct GLFWwindow;

namespace TGL
{
    class InputSystem : public Service<InputSystem>
    {
    private:
        friend class Application;

    private:
        GLFWwindow* m_WindowPtr = nullptr;

    private:
        std::unordered_set<KeyCode> m_KeysPressedThisFrame;
        std::unordered_set<KeyCode> m_KeysRepeatedThisFrame;
        std::unordered_set<KeyCode> m_KeysReleasedThisFrame;
        std::unordered_set<KeyCode> m_KeysDown;

        std::unordered_set<MouseButton> m_MouseButtonsPressedThisFrame;
        std::unordered_set<MouseButton> m_MouseButtonsReleasedThisFrame;
        std::unordered_set<MouseButton> m_MouseButtonsDown;

        glm::ivec2 m_MousePosition = { 0, 0 };
        glm::ivec2 m_LastMousePosition = { 0, 0 };

        glm::ivec2 m_MouseDelta = { 0, 0 };
        i32 m_MouseScroll = 0;

        MouseMode m_MouseMode = MouseMode::Normal;

    private:
        InputSystem() = default;
        ~InputSystem() = default;

    public:
        bool IsKeyDown(KeyCode key) const;
        bool WasKeyPressed(KeyCode key) const;
        bool WasKeyRepeated(KeyCode key) const;
        bool WasKeyReleased(KeyCode key) const;

        bool IsMouseButtonDown(MouseButton button) const;
        bool WasMouseButtonPressed(MouseButton button) const;
        bool WasMouseButtonReleased(MouseButton button) const;

        glm::ivec2 GetMousePosition() const;
        glm::ivec2 GetMouseDelta() const;
        void SetMousePosition(glm::ivec2 position);

        i32 GetMouseScroll() const;

        MouseMode GetMouseMode() const;
        void SetMouseMode(MouseMode mode);

    private:
        void Init(GLFWwindow *windowPtr);

    private:
        void OnEndOfFrame();

    private:
        static void KeyboardCallback(GLFWwindow *windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
        static void MouseButtonCallback(GLFWwindow *windowPtr, i32 button, i32 action, i32 mods);
        static void MousePositionCallback(GLFWwindow *windowPtr, f64 x, f64 y);
        static void MouseScrollCallback(GLFWwindow *windowPtr, f64 x, f64 y);
    };
}
