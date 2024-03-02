#include "window.h"
#include "Exceptions/Core/FailedToInitializeEngineException.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Util/DebugFeatures.hpp"

using namespace Engine::Core;
using namespace Engine::Exceptions::Core;

Window::Window(const char* title, unsigned int width, unsigned int height, bool vsync = true)
    : m_Data({title, {width, height}, vsync})
{}

void Window::Init()
{
    if (!glfwInit())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';

    m_WindowPtr = glfwCreateWindow(m_Data.m_Resolution.x, m_Data.m_Resolution.y, m_Data.m_Title, nullptr, nullptr);

    if (m_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_WindowPtr, &m_Data);

    glfwSetWindowSizeLimits(m_WindowPtr, 800, 450, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowPos(m_WindowPtr, 50, 50);

    glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* window, int width, int height)
    {
        WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->m_Resolution = {width, height};
        glViewport(0, 0, width, height);
    });

    glfwMakeContextCurrent(m_WindowPtr);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  // NOLINT
    {
        throw FailedToInitializeEngineException("Failed to init GLAD");
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    SetVsync(m_Data.m_Vsync);
}

void Window::Terminate()
{
    glfwDestroyWindow(m_WindowPtr);
    glfwTerminate();
}

void Window::UpdateBuffers()
{
    glfwSwapBuffers(m_WindowPtr);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_WindowPtr);
}

std::string Window::GetTitle()
{
    return m_Data.m_Title;
}


void Window::SetTitle(const char* title)
{
    glfwSetWindowTitle(m_WindowPtr, title);
}

bool Window::IsVsync()
{
    return m_Data.m_Vsync;
}

void Window::SetVsync(bool vsync)
{
    m_Data.m_Vsync = vsync;
    glfwSwapInterval(vsync);
}

void Window::SetResolution(glm::uvec2 resolution)
{
    glfwSetWindowSize(m_WindowPtr, resolution.x, resolution.y);
}

glm::uvec2 Window::GetResolution()
{
    return m_Data.m_Resolution;
}

GLFWwindow* Window::GetGlfwWindow()
{
    return m_WindowPtr;
}

WindowData* Window::GetDataPointer()
{
    return &m_Data;
}
