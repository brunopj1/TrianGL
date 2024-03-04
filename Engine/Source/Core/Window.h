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
        static Window* GetInstance();

    private:
        void Init();
        void Terminate() const;

    private:
        void ResizeCallback(int width, int height);

    private:
        void UpdateBuffers() const;
        void PollEvents() const;
        bool ShouldClose() const;

    public:
        std::string GetTitle();
        void SetTitle(std::string title);

        bool IsVsync() const;
        void SetVsync(bool vsync);

        glm::uvec2 GetResolution() const;
        void SetResolution(glm::uvec2 resolution) const;

        float GetAspectRatio() const;

    private:
        GLFWwindow* GetGlfwWindow() const;
    };
}
