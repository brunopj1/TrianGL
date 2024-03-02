#include "Application.h"

#include <glad/glad.h>

#include "Game/Entity.h"
#include "Game/GameMode.h"
#include "Exceptions/Core/GameModeMissingException.h"

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
    m_EntityManager.Terminate();

    Terminate();
}

void Application::Run()
{
    if (!m_EntityManager.m_GameMode)
    {
        throw Exceptions::Core::GameModeMissingException();
    }

    m_EntityManager.m_GameMode->OnStart();

    Loop();
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
}

void Application::Loop()
{
    while (!m_Window.ShouldClose())
    {
        Update();
        Render();
        m_Window.PollEvents();
    }
}

void Application::Update() const
{
    m_EntityManager.m_GameMode->OnEarlyUpdate();

    for (Game::Entity* entity : m_EntityManager.m_Entities)
    {
        entity->OnUpdate();
    }

    m_EntityManager.m_GameMode->OnLateUpdate();
}

void Application::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.31f, 0.37f, 0.56f, 1.0f);

#ifdef DEBUG
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif

#ifdef DEBUG
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

    m_Window.UpdateBuffers();
}

void Application::Terminate() const
{
    // ImGui
#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::Shutdown();
    ImGui::DestroyContext();
#endif

    // GLFW
    m_Window.Terminate();
}
