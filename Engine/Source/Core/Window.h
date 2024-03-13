#pragma once

#include <string>
#include <glm/vec2.hpp>

// Forward declarations
// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace TGL
{
    class Window
    {
    private:
        friend class Application;

    private:
        inline static Window* s_Instance = nullptr;

    private:
        GLFWwindow* m_WindowPtr = nullptr;

    private:
        std::string m_Title;
        glm::ivec2 m_Position;
        glm::uvec2 m_Resolution;
        float m_AspectRatio;
        bool m_Fullscreen;
        bool m_Vsync;

    private:
        Window(std::string title, glm::ivec2 position, glm::uvec2 resolution, bool fullscreen, bool vsync);
        ~Window() = default;

    public:
        static bool IsFullscreen();
        static void SetFullscreen(bool fullscreen);

        static std::string GetTitle();
        static void SetTitle(std::string title);

        static glm::ivec2 GetPosition();
        static void SetPosition(glm::ivec2 position);

        static glm::uvec2 GetResolution();
        static void SetResolution(glm::uvec2 resolution);

        static float GetAspectRatio();

        static bool IsVsync();
        static void SetVsync(bool vsync);

    private:
        void Init();
        void Terminate() const;

    private:
        void PositionCallback(int x, int y);
        void ResizeCallback(int width, int height);

    private:
        void SwapBuffers() const;
        void PollEvents() const;
        bool ShouldClose() const;

    private:
        GLFWwindow* GetGlfwWindow() const;
    };
}
