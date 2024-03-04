#include "Window.h"

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include "EntityManager.h"
#include "Entities/Camera.h"
#include "GLFW/glfw3.h"

#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <utility>

using namespace Engine::Core;
using namespace Engine::Exceptions::Core;

Window::Window(std::string title, const glm::uvec2 resolution, const bool vsync = true)
    : m_Title(std::move(title)), m_Resolution(resolution), m_AspectRatio(static_cast<float>(resolution.x) / static_cast<float>(resolution.y)), m_Vsync(vsync)
{
    s_Instance = this;
}

void Window::Init()
{
    m_WindowPtr = glfwCreateWindow(m_Resolution.x, m_Resolution.y, m_Title.c_str(), nullptr, nullptr);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

    if (m_WindowPtr == nullptr)
    {
        throw FailedToInitializeEngineException("Failed to create GLFW window");
    }

    glfwSetWindowSizeLimits(m_WindowPtr, 400, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowPos(m_WindowPtr, 50, 50);

    glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* _, const int width, const int height)
    {
        s_Instance->ResizeCallback(width, height);
    });

    glfwMakeContextCurrent(m_WindowPtr);

    SetVsync(m_Vsync);
}

void Window::Terminate() const
{
    glfwDestroyWindow(m_WindowPtr);
    glfwTerminate();
}

void Window::ResizeCallback(int width, int height)
{
    m_Resolution = {width, height};
    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glViewport(0, 0, width, height);

    for (const auto camera : EntityManager::FindEntities<Entities::Camera>())
    {
        camera->SetAspectRatio(m_AspectRatio);
    }
}

void Window::UpdateBuffers() const
{
    glfwSwapBuffers(m_WindowPtr);
}

// ReSharper disable once CppMemberFunctionMayBeStatic

void Window::PollEvents() const
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_WindowPtr);
}

std::string Window::GetTitle()
{
    return s_Instance->m_Title;
}


void Window::SetTitle(std::string title)
{
    s_Instance->m_Title = std::move(title);
    glfwSetWindowTitle(s_Instance->m_WindowPtr, s_Instance->m_Title.c_str());
}

bool Window::IsVsync()
{
    return s_Instance->m_Vsync;
}

void Window::SetVsync(const bool vsync)
{
    s_Instance->m_Vsync = vsync;
    glfwSwapInterval(vsync);
}

glm::uvec2 Window::GetResolution()
{
    return s_Instance->m_Resolution;
}

void Window::SetResolution(const glm::uvec2 resolution)
{
    glfwSetWindowSize(s_Instance->m_WindowPtr, resolution.x, resolution.y);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
}

float Window::GetAspectRatio()
{
    return s_Instance->m_AspectRatio;
}

GLFWwindow* Window::GetGlfwWindow() const
{
    return m_WindowPtr;
}
