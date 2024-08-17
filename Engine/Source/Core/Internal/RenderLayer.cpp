#include "RenderLayer.h"

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef DEBUG
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

#ifdef DEBUG
#include <iostream>
#include <format>
#endif

using namespace TGL;

void RenderLayer::SetErrorCallback(void (*func)(i32, const char*))
{
    glfwSetErrorCallback(func);
}

void RenderLayer::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
    glfwSetWindowPosCallback(windowPtr, func);
}

void RenderLayer::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32))
{
    glfwSetWindowSizeCallback(windowPtr, func);
}

void RenderLayer::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
    glfwSetWindowMaximizeCallback(windowPtr, func);
}

void RenderLayer::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32))
{
    glfwSetWindowIconifyCallback(windowPtr, func);
}

bool RenderLayer::InitGlfw()
{
    return glfwInit();
}

bool RenderLayer::InitGlad()
{
    return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); // NOLINT(clang-diagnostic-cast-function-type-strict)
}

bool RenderLayer::InitImgui(GLFWwindow* windowPtr)
{
#ifdef DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(windowPtr, true))
    {
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 430"))
    {
        return false;
    }

    return true;
#endif
}

void RenderLayer::SetupOpenGlVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void RenderLayer::DebugVersions()
{
#ifdef DEBUG
    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Dear ImGui version: " << ImGui::GetVersion() << '\n';
#endif
}

void RenderLayer::TerminateGlfw()
{
    glfwTerminate();
}

void RenderLayer::TerminateImgui()
{
#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif
}

GLFWwindow* RenderLayer::CreateWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution)
{
    GLFWwindow* windowPtr = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), nullptr, nullptr);

    if (windowPtr != nullptr)
    {
        glfwMakeContextCurrent(windowPtr);
    }

    glfwSetWindowSizeLimits(windowPtr, minResolution.x, minResolution.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

    return windowPtr;
}

void RenderLayer::DestroyWindow(GLFWwindow* windowPtr)
{
    glfwDestroyWindow(windowPtr);
}

void RenderLayer::ClearBuffers(const glm::vec3& color)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void RenderLayer::SwapBuffers(GLFWwindow* windowPtr)
{
    glfwSwapBuffers(windowPtr);
}

void RenderLayer::PollEvents()
{
    glfwPollEvents();
}

void RenderLayer::PrepareImguiFrame()
{
#ifdef DEBUG
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif
}

void RenderLayer::RenderImguiFrame()
{
#ifdef DEBUG
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void RenderLayer::RenderImGuiDebugInfo(const u32 framerate, const u32 entityCount, const u32 componentCount)
{
#ifdef DEBUG
    const f32 frameTime = 1000.0f / (framerate != 0 ? framerate : 1);

    std::string message = std::format("Framerate: {0} ({1:.3f} ms)\n", framerate, frameTime);
    message += std::format("Entities: {0} | Components: {1}", entityCount, componentCount);

    const char* cMessage = message.c_str();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 windowPos = viewport->WorkPos + ImVec2(10, viewport->WorkSize.y - ImGui::CalcTextSize(cMessage).y - 10);

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->AddText(windowPos, IM_COL32(255, 255, 255, 255), cMessage);
#endif
}

void RenderLayer::CloseWindow(GLFWwindow* windowPtr)
{
    glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
}

bool RenderLayer::ShouldCloseWindow(GLFWwindow* windowPtr)
{
    return glfwWindowShouldClose(windowPtr);
}

void RenderLayer::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title)
{
    glfwSetWindowTitle(windowPtr, title.c_str());
}

void RenderLayer::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
    glfwSetWindowPos(windowPtr, position.x, position.y);
}

void RenderLayer::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
    glfwSetWindowSize(windowPtr, resolution.x, resolution.y);
}

void RenderLayer::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
    glfwSetWindowMonitor(
        windowPtr,
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        position.x, position.y,
        resolution.x, resolution.y,
        GLFW_DONT_CARE
    );
}

void RenderLayer::MaximizeWindow(GLFWwindow* windowPtr)
{
    glfwMaximizeWindow(windowPtr);
}

void RenderLayer::MinimizeWindow(GLFWwindow* windowPtr)
{
    glfwIconifyWindow(windowPtr);
}

void RenderLayer::RestoreWindow(GLFWwindow* windowPtr)
{
    glfwRestoreWindow(windowPtr);
}

bool RenderLayer::IsMaximized(GLFWwindow* windowPtr)
{
    return glfwGetWindowAttrib(windowPtr, GLFW_MAXIMIZED);
}

bool RenderLayer::IsMinimized(GLFWwindow* windowPtr)
{
    return glfwGetWindowAttrib(windowPtr, GLFW_ICONIFIED);
}

void RenderLayer::SetSwapInterval(const bool vsync)
{
    glfwSwapInterval(vsync);
}

void RenderLayer::SetViewport(const glm::uvec2& resolution)
{
    glViewport(0, 0, resolution.x, resolution.y);
}
