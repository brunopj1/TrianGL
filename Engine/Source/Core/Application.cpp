#include "Application.h"

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Components/TextureRenderer.h"

#include "Services/InputSystem.h"
#include "Services/EntityManager.h"
#include "Entities/Camera.h"
#include "Exceptions/Core/FailedToInitializeEngineException.hpp"

#include "Game/GameMode.h"
#include "Exceptions/Game/MissingGameModeException.hpp"
#include "Exceptions/OpenGL/OpenGlException.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#ifdef DEBUG
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#endif

using namespace Engine::Core;

Application::Application(const ApplicationConfig& config)
    : m_Window(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync)
{
    Init();
}

Application::~Application()
{
    Terminate();
}

void Application::Run()
{
    if (!m_EntityManager.m_GameMode)
    {
        throw Exceptions::Game::GameModeMissingException();
    }

    m_EntityManager.m_GameMode->OnStart();

    while (!m_Window.ShouldClose())
    {
        Update();

        Render();

        m_InputSystem.OnEndOfFrame();

        PollEvents();
    }
}

void Application::Init()
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        throw Exceptions::Core::FailedToInitializeEngineException("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window.Init();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  // NOLINT(clang-diagnostic-cast-function-type-strict)
    {
        throw Exceptions::Core::FailedToInitializeEngineException("Failed to init GLAD");
    }

#ifdef DEBUG
    IMGUI_CHECKVERSION();
    ImGuiContext* context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif

    stbi_set_flip_vertically_on_load(true);

#ifdef DEBUG
    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Dear ImGui version: " << ImGui::GetVersion() << '\n';
#endif

    m_InputSystem.Init(m_Window.GetGlfwWindow());

    Components::TextureRenderer::Init();
}

void Application::Terminate() const
{
    Components::TextureRenderer::Terminate();

#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::Shutdown();
    ImGui::DestroyContext();
#endif

    m_Window.Terminate();
}

void Application::Update()
{
    const float deltaTime = m_Clock.Update();

    m_EntityManager.Update(deltaTime);
}

void Application::Render() const
{
    const Entities::Camera* camera = Entities::Camera::GetMainCamera();

    const glm::vec3 backgroundColor = camera != nullptr ? camera->GetBackgroundColor() : glm::vec3(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);

#ifdef DEBUG
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif

    if (camera != nullptr)
    {
        m_EntityManager.Render();
    }

#ifdef DEBUG
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

    m_Window.UpdateBuffers();
}

void Application::PollEvents() const
{
    m_Window.PollEvents();
}

void Application::ErrorCallback(const int error, const char* description)
{
    throw Exceptions::OpenGl::OpenGlException(error, description);
}
