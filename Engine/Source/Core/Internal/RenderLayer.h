#pragma once

#include "Core/DataTypes.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <string>

// Forward declarations
// ReSharper disable once CppInconsistentNaming, IdentifierTypo
struct GLFWwindow;

namespace TGL
{
    class RenderLayer
    {
    private:
        friend class Application;
        friend class Window;
        
    public:
        RenderLayer() = delete;
        ~RenderLayer() = delete;

    private:
        static void SetErrorCallback(void(*func)(i32, const char*));

        static void SetWindowPositionCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32));
        static void SetWindowSizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32));
        static void SetWindowMaximizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32));
        static void SetWindowMinimizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32));
        
    private:
        static bool InitGlfw();
        static bool InitGlad();
        static bool InitImgui(GLFWwindow* windowPtr);
        
        static void SetupOpenGlVersion();
        static void DebugVersions();

        static void TerminateGlfw();
        static void TerminateImgui();
        
        static GLFWwindow* CreateWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution);
        static void DestroyWindow(GLFWwindow* windowPtr);

    private:
        static void ClearBuffers(const glm::vec3& color);
        static void SwapBuffers(GLFWwindow* windowPtr);
        static void PollEvents();

    private:
        static void PrepareImguiFrame();
        static void RenderImguiFrame();
        static void RenderImGuiDebugInfo(u32 framerate, u32 entityCount, u32 componentCount);

    private:
        static void CloseWindow(GLFWwindow* windowPtr);
        static bool ShouldCloseWindow(GLFWwindow* windowPtr);
        
    private:
        static void SetWindowTitle(GLFWwindow* windowPtr, const std::string& title);
        static void SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position);
        static void SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution);
        
    private:
        static void SetFullscreen(GLFWwindow* windowPtr, bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution);
        static void MaximizeWindow(GLFWwindow* windowPtr);
        static void MinimizeWindow(GLFWwindow* windowPtr);
        static void RestoreWindow(GLFWwindow* windowPtr);

        static bool IsMaximized(GLFWwindow* windowPtr);
        static bool IsMinimized(GLFWwindow* windowPtr);

    private:
        static void SetSwapInterval(bool vsync);

        static void SetViewport(const glm::uvec2& resolution);
    };
}

