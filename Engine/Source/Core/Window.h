#pragma once

#include "DataTypes.h"
#include "Service.h"
#include <string>
#include <glm/vec2.hpp>

// Forward declarations
// ReSharper disable once CppInconsistentNaming, IdentifierTypo
struct GLFWwindow;

namespace TGL
{
    class Window : public Service<Window>
    {
    private:
        friend class Application;
        friend class RenderLayer;

    private:
        GLFWwindow* m_WindowPtr = nullptr;

    private:
        std::string m_Title;
        glm::ivec2 m_Position;
        glm::uvec2 m_Resolution;
        f32 m_AspectRatio;
        bool m_Fullscreen;
        bool m_Vsync;

    private:
        Window() = default;
        ~Window() = default;

    public:
        bool IsFullscreen() const;
        void SetFullscreen(bool fullscreen);

        bool IsMaximized() const;
        void Maximize();

        bool IsMinimized() const;
        void Minimize();

        void Restore();

        std::string GetTitle();
        void SetTitle(const std::string& title);

        glm::ivec2 GetPosition() const;
        void SetPosition(glm::ivec2 position);

        glm::uvec2 GetResolution() const;
        void SetResolution(glm::uvec2 resolution);

        f32 GetAspectRatio() const;

        bool IsVsync() const;
        void SetVsync(bool vsync);

        void Close();

    private:
        bool ShouldClose() const;

    private:
        GLFWwindow* Init(std::string title, glm::ivec2 position, glm::uvec2 resolution, bool fullscreen, bool vsync);
        void Terminate() const;

    private:
        static void PositionCallback(GLFWwindow* windowPtr, i32 x, i32 y);
        static void SizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

        static void FullscreenCallback(bool fullscreen);
        static void MaximizeCallback(GLFWwindow* windowPtr, i32 maximized);
        static void MinimizeCallback(GLFWwindow* windowPtr, i32 minimized);

    private:
        GLFWwindow* GetGlfwWindow() const;
    };
}
