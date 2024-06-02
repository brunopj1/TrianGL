#include <Core/Application.h>

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include "Assets/Internal/Quad.h"
#include <GLFW/glfw3.h>

#include <Core/Window.h>
#include <Core/Clock.h>
#include <Implementations/Components/SpriteRenderer.h>

#include <Implementations/Entities/Camera.h>
#include <Exceptions/Core/FailedToInitializeEngineException.h>

#include <Exceptions/Game/MissingGameModeException.h>
#include <Exceptions/OpenGL/OpenGlException.h>

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
{
    Init(config);
}

Application::~Application()
{
    Terminate();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Application::Run()
{
    GameMode* gameMode = EntityManager::GetGameMode();

    if (gameMode == nullptr)
    {
        throw GameModeMissingException();
    }

    gameMode->OnStart();

    while (!Window::ShouldClose())
    {
        PollEvents();

        NewFrame();

        Cleanup();
    }
}

void Application::Init(const ApplicationConfig& config)
{
    // Enable the availability flag
    s_IsAvailable = true;
    
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window::Init(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) // NOLINT(clang-diagnostic-cast-function-type-strict)
    {
        throw FailedToInitializeEngineException("Failed to init GLAD");
    }

#ifdef DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(Window::GetGlfwWindow(), true))
    {
        throw FailedToInitializeEngineException("Failed to init ImGui for GLFW");
    }

    if (!ImGui_ImplOpenGL3_Init("#version 430"))
    {
        throw FailedToInitializeEngineException("Failed to init ImGui for OpenGL 3");
    }
#endif

#ifdef DEBUG
    std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Dear ImGui version: " << ImGui::GetVersion() << '\n';
#endif

    // Core systems
    InputSystem::Init(Window::GetGlfwWindow());
    AssetManager::Init();
    EntityManager::Init();
}

void Application::Terminate()
{
    // Core systems
    EntityManager::Terminate();
    AssetManager::Terminate();
    InputSystem::Terminate();

#ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif

    Window::Terminate();
    
    // Disable the availability flag
    s_IsAvailable = false;
}

void Application::NewFrame()
{
    // Prepare the ImGui frame

#ifdef DEBUG
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif

    // Update

    const float deltaTime = Clock::Update();
    EntityManager::Update(deltaTime);

    // Render

    Camera* camera = Camera::GetMainCamera();
    if (camera != nullptr) camera->UpdateMatrices();

    const glm::vec3 backgroundColor = camera != nullptr ? camera->GetBackgroundColor() : glm::vec3(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);

    if (camera != nullptr)
    {
        EntityManager::Render();
    }

#ifdef DEBUG
    RenderDebugInfo();
#endif

#ifdef DEBUG
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

    Window::SwapBuffers();
}

void Application::Cleanup()
{
    InputSystem::OnEndOfFrame();
}

void Application::PollEvents()
{
    Window::PollEvents();
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
