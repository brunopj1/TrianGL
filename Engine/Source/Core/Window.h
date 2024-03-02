#pragma once

#include <string>
#include <glm/vec2.hpp>

// Forward declarations
struct GLFWwindow;

namespace Engine::Core
{
    struct WindowData
    {
        const char* m_Title;
        glm::uvec2 m_Resolution;
        bool m_Vsync;
    };

    class Window
    {
    private:
        friend class Application;

    private:
        GLFWwindow* m_WindowPtr = nullptr;
        WindowData m_Data;

    private:
        Window(const char* title, unsigned int width, unsigned int height, bool vsync);
        ~Window() = default;

    private:
        void Init();
        void Terminate();

        void UpdateBuffers();
        void PollEvents();

        bool ShouldClose();

    public:
        std::string GetTitle();
        void SetTitle(const char* title);

        bool IsVsync();
        void SetVsync(bool vsync);

        void SetResolution(glm::uvec2 resolution);
        glm::uvec2 GetResolution();

    private:
        GLFWwindow* GetGlfwWindow();
        WindowData* GetDataPointer();
    };
}
