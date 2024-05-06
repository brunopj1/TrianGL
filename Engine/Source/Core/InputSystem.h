#pragma once

#include <Core/InputCodes.h>
#include <glm/vec2.hpp>
#include <unordered_set>

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
        static inline int s_MouseScroll = 0;

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

        static int GetMouseScroll();

        static MouseMode GetMouseMode();
        static void SetMouseMode(MouseMode mode);

    private:
        static void Init(GLFWwindow* windowPtr);
        static void Terminate();

        static void OnEndOfFrame();

    private:
        static void KeyboardCallback(int key, int action, int mods);
        static void MouseButtonCallback(int button, int action, int mods);
        static void MousePositionCallback(double x, double y);
        static void MouseScrollCallback(double x, double y);
    };
}
