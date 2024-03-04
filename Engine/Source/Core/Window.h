#pragma once

#include <string>
#include <glm/vec2.hpp>

// Forward declarations
// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace Engine::Core
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
        glm::uvec2 m_Resolution;
        float m_AspectRatio;
        bool m_Vsync;

    private:
        Window(std::string title, glm::uvec2 resolution, bool vsync);
        ~Window() = default;

    public:
        static std::string GetTitle();
        static void SetTitle(std::string title);

        static bool IsVsync();
        static void SetVsync(bool vsync);

        static glm::uvec2 GetResolution();
        static void SetResolution(glm::uvec2 resolution);

        static float GetAspectRatio();

    private:
        void Init();
        void Terminate() const;

    private:
        void ResizeCallback(int width, int height);

    private:
        void UpdateBuffers() const;
        void PollEvents() const;
        bool ShouldClose() const;

    private:
        GLFWwindow* GetGlfwWindow() const;
    };
}
