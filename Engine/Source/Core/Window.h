#pragma once

#include <string>
#include <glm/vec2.hpp>

// Forward declarations
// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace Engine::Core
{
    struct WindowData
    {
        // ReSharper disable CppInconsistentNaming

        std::string Title;
        glm::uvec2 Resolution;
        bool Vsync;

        // ReSharper restore CppInconsistentNaming
    };

    class Window
    {
    private:
        friend class Application;

    private:
        GLFWwindow* m_WindowPtr = nullptr;
        WindowData m_Data;

    private:
        Window(std::string title, glm::uvec2 resolution, bool vsync);
        ~Window() = default;

    private:
        void Init();
        void Terminate() const;

        void UpdateBuffers() const;
        void PollEvents();

        bool ShouldClose() const;

    public:
        std::string GetTitle();
        void SetTitle(std::string title);

        bool IsVsync() const;
        void SetVsync(bool vsync);

        void SetResolution(glm::uvec2 resolution) const;
        glm::uvec2 GetResolution() const;

    private:
        GLFWwindow* GetGlfwWindow() const;
        WindowData* GetDataPointer();
    };
}
