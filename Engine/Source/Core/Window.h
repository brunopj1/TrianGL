#pragma once

#include "DataTypes.h"
#include <string>
#include <glm/vec2.hpp>

// Forward declarations
// ReSharper disable once CppInconsistentNaming, IdentifierTypo
struct GLFWwindow;

namespace TGL
{
    class Window
    {
    private:
        friend class Application;

    private:
        static inline GLFWwindow* s_WindowPtr = nullptr;

    private:
        static inline std::string s_Title;
        static inline glm::ivec2 s_Position;
        static inline glm::uvec2 s_Resolution;
        static inline f32 s_AspectRatio;
        static inline bool s_Fullscreen;
        static inline bool s_Vsync;

    public:
        Window() = delete;
        ~Window() = delete;

    public:
        static bool IsFullscreen();
        static void SetFullscreen(bool fullscreen);

        static bool IsMaximized();
        static void Maximize();

        static bool IsMinimized();
        static void Minimize();

        static void Restore();

        static std::string GetTitle();
        static void SetTitle(const std::string& title);

        static glm::ivec2 GetPosition();
        static void SetPosition(glm::ivec2 position);

        static glm::uvec2 GetResolution();
        static void SetResolution(glm::uvec2 resolution);

        static f32 GetAspectRatio();

        static bool IsVsync();
        static void SetVsync(bool vsync);

        static void Close();

    private:
        static void Init(std::string title, glm::ivec2 position, glm::uvec2 resolution, bool fullscreen, bool vsync);
        static void Terminate();

    private:
        static void PositionCallback(i32 x, i32 y);
        static void SizeCallback(i32 width, i32 height);

        static void FullscreenCallback(bool fullscreen);
        static void MaximizeCallback();
        static void MinimizeCallback();
        static void RestoreCallback();

    private:
        static void SwapBuffers();
        static void PollEvents();
        static bool ShouldClose();

    private:
        static GLFWwindow* GetGlfwWindow();
    };
}
