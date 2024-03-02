#include "Window.h"

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include "Exceptions/Core/OpenGlException.h"
#include <iostream>

using namespace Engine::Core;
using namespace Engine::Exceptions::Core;

Window::Window(std::string title, const glm::uvec2 resolution, const bool vsync = true)
    : m_Data({std::move(title), resolution, vsync})
{}

void Window::Init()
{
    glfwSetErrorCallback([](const int error, const char* description)
    {
        throw OpenGlException(error, description);
    });

    if (!glfwInit())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_WindowPtr = glfwCreateWindow(m_Data.Resolution.x, m_Data.Resolution.y, m_Data.Title.c_str(), nullptr, nullptr);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

    if (m_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_WindowPtr, &m_Data);

    glfwSetWindowSizeLimits(m_WindowPtr, 400, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowPos(m_WindowPtr, 50, 50);

    glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* window, int width, int height)
    {
        WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->Resolution = {width, height};
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(m_WindowPtr);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  // NOLINT
    {
        throw FailedToInitializeEngineException("Failed to init GLAD");
    }

    SetVsync(m_Data.Vsync);

#ifdef DEBUG
    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
#endif
}

void Window::Terminate() const
{
    glfwDestroyWindow(m_WindowPtr);
    glfwTerminate();
}

void Window::UpdateBuffers() const
{
    glfwSwapBuffers(m_WindowPtr);
}

// ReSharper disable once CppMemberFunctionMayBeStatic

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_WindowPtr);
}

std::string Window::GetTitle()
{
    return m_Data.Title;
}


void Window::SetTitle(std::string title)
{
    m_Data.Title = std::move(title);
    glfwSetWindowTitle(m_WindowPtr, m_Data.Title.c_str());
}

bool Window::IsVsync() const
{
    return m_Data.Vsync;
}

void Window::SetVsync(const bool vsync)
{
    m_Data.Vsync = vsync;
    glfwSwapInterval(vsync);
}

void Window::SetResolution(const glm::uvec2 resolution) const
{
    glfwSetWindowSize(m_WindowPtr, resolution.x, resolution.y);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
}

glm::uvec2 Window::GetResolution() const
{
    return m_Data.Resolution;
}

GLFWwindow* Window::GetGlfwWindow() const
{
    return m_WindowPtr;
}

WindowData* Window::GetDataPointer()
{
    return &m_Data;
}
