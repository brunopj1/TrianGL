#pragma once

#include "DataTypes.h"
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
    class InputSystem final
    {
    private:
        friend class Application;

    private:
        static inline GLFWwindow *s_WindowPtr = nullptr;

    private:
        static inline std::unordered_set<KeyCode> s_KeysPressedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysRepeatedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysReleasedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysDown;

        static inline std::unordered_set<MouseButton> s_MouseButtonsPressedThisFrame;
        static inline std::unordered_set<MouseButton> s_MouseButtonsReleasedThisFrame;
        static inline std::unordered_set<MouseButton> s_MouseButtonsDown;

        static inline glm::ivec2 s_MousePosition;
        static inline glm::ivec2 s_LastMousePosition;

        static inline glm::ivec2 s_MouseDelta;
        static inline i32 s_MouseScroll;

        static inline MouseMode s_MouseMode;

    public:
        InputSystem() = delete;
        ~InputSystem() = delete;

    public:
        static bool IsKeyDown(KeyCode key);
        static bool WasKeyPressed(KeyCode key);
        static bool WasKeyRepeated(KeyCode key);
        static bool WasKeyReleased(KeyCode key);

        static bool IsMouseButtonDown(MouseButton button);
        static bool WasMouseButtonPressed(MouseButton button);
        static bool WasMouseButtonReleased(MouseButton button);

        static glm::ivec2 GetMousePosition();
        static glm::ivec2 GetMouseDelta();
        static void SetMousePosition(glm::ivec2 position);

        static i32 GetMouseScroll();

        static MouseMode GetMouseMode();
        static void SetMouseMode(MouseMode mode);

    private:
        static void Init(GLFWwindow *windowPtr);
        static void Terminate();

        static void OnEndOfFrame();

    private:
        static void KeyboardCallback(GLFWwindow *windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
        static void MouseButtonCallback(GLFWwindow *windowPtr, i32 button, i32 action, i32 mods);
        static void MousePositionCallback(GLFWwindow *windowPtr, f64 x, f64 y);
        static void MouseScrollCallback(GLFWwindow *windowPtr, f64 x, f64 y);
    };
}
