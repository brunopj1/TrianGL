#include "Application.h"

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include "glad/glad.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Implementations/Components/SpriteRenderer.h"

#include "Implementations/Entities/Camera.h"
#include "Exceptions/Core/FailedToInitializeEngineException.h"

#include "Exceptions/Game/MissingGameModeException.h"
#include "Exceptions/OpenGL/OpenGlException.h"

#ifdef DEBUG
#include <iostream>
#endif

#ifdef DEBUG
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

using namespace TGL;

Application::Application(const ApplicationConfig& config)
    : m_Window(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync)
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
        throw GameModeMissingException();
    }

    m_EntityManager.m_GameMode->OnStart();

    while (!m_Window.ShouldClose())
    {
        PollEvents();

        Update();

        Render();

        Cleanup();
    }
}

void Application::Init()
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window.Init();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))  // NOLINT(clang-diagnostic-cast-function-type-strict)
    {
        throw FailedToInitializeEngineException("Failed to init GLAD");
    }

#ifdef DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGlfwWindow(), true))
    {
        throw FailedToInitializeEngineException("Failed to init ImGui for GLFW");
    }

    if (!ImGui_ImplOpenGL3_Init("#version 430"))
    {
        throw FailedToInitializeEngineException("Failed to init ImGui for OpenGL 3");
    }
#endif

    stbi_set_flip_vertically_on_load(true);

#ifdef DEBUG
    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Dear ImGui version: " << ImGui::GetVersion() << '\n';
#endif

    m_InputSystem.Init(m_Window.GetGlfwWindow());

    SpriteRenderer::Init();
}

void Application::Terminate() const
{
    SpriteRenderer::Terminate();

#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
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
    Camera* camera = Camera::GetMainCamera();
    camera->UpdateMatrices();

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
    RenderDebugInfo();
#endif

#ifdef DEBUG
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

    m_Window.SwapBuffers();
}

void Application::Cleanup()
{
    m_InputSystem.OnEndOfFrame();
}

void Application::PollEvents() const
{
    m_Window.PollEvents();
}

#ifdef DEBUG

void Application::RenderDebugInfo()
{
    const unsigned int framerate = Clock::GetFrameRate();
    const float frameTime = 1000.0f / (framerate != 0 ? framerate : 1);

    std::string message = std::format("Framerate: {0} ({1:.3f} ms)\n", framerate, frameTime);
    message += std::format("Entities: {0} | Components: {1}", EntityManager::GetEntityCount(), EntityManager::GetComponentCount());

    const char* cMessage = message.c_str();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 windowPos = viewport->WorkPos + ImVec2(10, viewport->WorkSize.y - ImGui::CalcTextSize(cMessage).y - 10);

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->AddText(windowPos, IM_COL32(255, 255, 255, 255), cMessage);
}

#endif

void Application::ErrorCallback(const int error, const char* description)
{
    throw OpenGlException(error, description);
}
