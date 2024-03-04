#include "Application.h"

#include "Entities/Camera.h"
#include <glad/glad.h>

#include "Game/GameMode.h"
#include "Exceptions/Core/GameModeMissingException.h"
#include "Exceptions/Core/MissingMainCameraException.h"

#ifdef DEBUG
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#endif

using namespace Engine::Core;

Application::Application(const ApplicationConfig& config)
    : m_Window(config.Title, config.Resolution, config.Vsync)
{
    Init();
}

Application::~Application()
{
    Terminate();
}

void Application::Init()
{
    m_Window.Init();

#ifdef DEBUG
    IMGUI_CHECKVERSION();
    ImGuiContext* context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);
    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif

    m_EntityManager.InitializeComponents();
}

void Application::Terminate()
{
    m_EntityManager.TerminateComponents();

#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::Shutdown();
    ImGui::DestroyContext();
#endif

    m_Window.Terminate();
}

void Application::Run()
{
    if (!m_EntityManager.m_GameMode)
    {
        throw Exceptions::Core::GameModeMissingException();
    }

    m_EntityManager.m_GameMode->OnStart();

    while (!m_Window.ShouldClose())
    {
        Update();

        Render();

        PollEvents();
    }
}

void Application::Update()
{
    m_EntityManager.Update();
}

void Application::Render() const
{
    const Entities::Camera* camera = Entities::Camera::GetMainCamera();
    if (camera == nullptr)
    {
        throw Exceptions::Core::MissingMainCameraException();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

#ifdef DEBUG
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif

    m_EntityManager.Render();

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
