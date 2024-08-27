#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <Core/Application.h>
#include <Core/Window.h>
#include <Core/Clock.h>
#include "Internal/RenderLayer.h"

#include <Implementations/Components/SpriteRenderer.h>
#include <Implementations/Entities/Camera.h>

#include <Exceptions/OpenGL/OpenGlException.h>

using namespace TGL;

Application::Application(const ApplicationConfig& config)
{
    Init(config);
}

Application::~Application()
{
    Terminate();
}

void Application::Init(const ApplicationConfig& config)
{
    // Update the status
    ApplicationStatus::SetStatus(ApplicationStatusValue::Initializing);

    // Init GLFW, GLAD, IMGUI    
    RenderLayer::SetErrorCallback(ErrorCallback);
    
    if (!RenderLayer::InitGlfw())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }
    
    RenderLayer::SetupOpenGlVersion(4, 3, true);

    const auto windowPtr = Window::Init(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync);
    
    if (!RenderLayer::InitGlad())
    {
        throw FailedToInitializeEngineException("Failed to init Glad");
    }

    if (!RenderLayer::InitImgui(windowPtr))
    {
        throw FailedToInitializeEngineException("Failed to init Imgui");
    }

    RenderLayer::DebugVersions();

    // OpenGL settings
    RenderLayer::SetupOpenGlSettings();
    
    // Core systems
    Clock::Init();
    InputSystem::Init(windowPtr);
    AssetManager::Init();
    EntityManager::Init();

    // Update the status
    ApplicationStatus::SetStatus(ApplicationStatusValue::PostInit);
}

void Application::GameLoop(GameMode* gameMode)
{
    gameMode->OnStart();

    while (!Window::ShouldClose())
    {
        RenderLayer::PollEvents();

        NewFrame();

        Cleanup();
    }
}

void Application::Terminate()
{
    // Update the status
    ApplicationStatus::SetStatus(ApplicationStatusValue::Terminating);

    // Core systems
    EntityManager::Terminate();
    AssetManager::Terminate();
    InputSystem::Terminate();

    RenderLayer::TerminateImgui();

    Window::Terminate();

    RenderLayer::TerminateGlfw();

    // Update the status
    ApplicationStatus::SetStatus(ApplicationStatusValue::Closed);
}

void Application::NewFrame()
{
    RenderLayer::PrepareImguiFrame();

    // Update

    const f32 deltaTime = Clock::Update();
    EntityManager::Update(deltaTime);

    // Render

    Camera* camera = Camera::GetMainCamera();
    if (camera != nullptr) camera->UpdateMatrices();

    const glm::vec3 backgroundColor = camera != nullptr ? camera->GetBackgroundColor() : glm::vec3(0.0f);
    RenderLayer::ClearBuffers(backgroundColor);

    if (camera != nullptr)
    {
        EntityManager::Render();
    }

#ifdef DEBUG
    const u32 framerate = Clock::GetFrameRate();
    const u32 entityCount = EntityManager::GetEntityCount();
    const u32 componentCount = EntityManager::GetComponentCount();
    RenderLayer::RenderImGuiDebugInfo(framerate, entityCount, componentCount);
#endif

    RenderLayer::RenderImguiFrame();

    RenderLayer::SwapBuffers(Window::GetGlfwWindow());
}

void Application::Cleanup()
{
    InputSystem::OnEndOfFrame();
}

void Application::ErrorCallback(const i32 error, const char* description)
{
    throw OpenGlException(error, description);
}
