#pragma once

#include "InputCodes.hpp"
#include "glm/vec2.hpp"
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
        static inline InputSystem* s_Instance = nullptr;

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

        glm::ivec2 m_MousePosition = {0, 0};
        glm::ivec2 m_LastMousePosition = {0, 0};

        glm::ivec2 m_MouseDelta = {0, 0};
        int m_MouseScroll = 0;

        MouseMode m_MouseMode = MouseMode::Normal;

    private:
        InputSystem();
        ~InputSystem();

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
        void Init(GLFWwindow* windowPtr);
        void OnEndOfFrame();

    private:
        void KeyboardCallback(int key, int action, int mods);
        void MouseButtonCallback(int button, int action, int mods);
        void MousePositionCallback(double x, double y);
        void MouseScrollCallback(double x, double y);
    };
}
