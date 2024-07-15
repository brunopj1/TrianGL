#pragma once

#include "DataTypes.h"
#include <Core/InputCodes.h>
#include <glm/vec2.hpp>
#include <unordered_set>

// TODO dont register the input if the user is interacting with ImGui

// Forward declarations
// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace TGL
{
    class InputSystem final
    {
    private:
        friend class Application;

    private:
        static inline GLFWwindow* s_WindowPtr = nullptr;

    private:
        static inline std::unordered_set<KeyCode> s_KeysPressedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysRepeatedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysReleasedThisFrame;
        static inline std::unordered_set<KeyCode> s_KeysDown;

        static inline std::unordered_set<MouseButton> s_MouseButtonsPressedThisFrame;
        static inline std::unordered_set<MouseButton> s_MouseButtonsReleasedThisFrame;
        static inline std::unordered_set<MouseButton> s_MouseButtonsDown;

        static inline glm::ivec2 s_MousePosition = {0, 0};
        static inline glm::ivec2 s_LastMousePosition = {0, 0};

        static inline glm::ivec2 s_MouseDelta = {0, 0};
        static inline i32 s_MouseScroll = 0;

        static inline MouseMode s_MouseMode = MouseMode::Normal;

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
        static void Init(GLFWwindow* windowPtr);
        static void Terminate();

        static void OnEndOfFrame();

    private:
        static void KeyboardCallback(i32 key, i32 action, i32 mods);
        static void MouseButtonCallback(i32 button, i32 action, i32 mods);
        static void MousePositionCallback(f64 x, f64 y);
        static void MouseScrollCallback(f64 x, f64 y);
    };
}
