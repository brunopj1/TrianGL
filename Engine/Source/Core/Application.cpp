#include <Core/Application.h>
#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <Core/Window.h>
#include <Core/Clock.h>
#include "Internal/RenderLayer.h"

#include <Implementations/Components/SpriteRenderer.h>
#include <Implementations/Entities/Camera.h>

#include <Exceptions/OpenGL/OpenGlException.h>

using namespace TGL;

Application::Application(const ApplicationConfig& config)
{
    s_Running = true;
    
    Init(config);
}

Application::~Application()
{
    Terminate();

    s_Running = false;
}

void Application::Init(const ApplicationConfig& config)
{
    // Init GLFW, GLAD, IMGUI    
    RenderLayer::SetErrorCallback(ErrorCallback);
    
    if (!RenderLayer::InitGlfw())
    {
        throw FailedToInitializeEngineException("Failed to init GLFW");
    }
    
    RenderLayer::SetupOpenGlVersion(4, 3, true);

    const auto windowPtr = m_Window.Init(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync);
    
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
    
    // Public services
    m_InputSystem.Init(windowPtr);

    // Private services
    m_AssetManager.Init();
    m_EntityManager.Init();
}

void Application::GameLoop(GameMode* gameMode)
{
    // Start the clock
    m_Clock.Start();

    // Start the game mode
    gameMode->OnStart();

    // Run the game loop
    while (!m_Window.ShouldClose())
    {
        RenderLayer::PollEvents();

        NewFrame();

        Cleanup();
    }
}

void Application::Terminate()
{
    // Private services
    m_EntityManager.Terminate();
    m_AssetManager.Terminate();

    RenderLayer::TerminateImgui();

    m_Window.Terminate();

    RenderLayer::TerminateGlfw();
}

void Application::NewFrame()
{
    RenderLayer::PrepareImguiFrame();

    // Update
    
    const f32 deltaTime = m_Clock.Update();
    m_EntityManager.Update(deltaTime);

    // Render

    Camera* camera = Camera::GetMainCamera();
    if (camera != nullptr) camera->UpdateMatrices();

    const glm::vec3 backgroundColor = camera != nullptr ? camera->GetBackgroundColor() : glm::vec3(0.0f);
    RenderLayer::ClearBuffers(backgroundColor);

    if (camera != nullptr)
    {
        m_EntityManager.Render();
    }

#ifdef DEBUG
#ifdef IMGUI
    const u32 framerate = m_Clock.GetFrameRate();
    const u32 entityCount = m_EntityManager.GetEntityCount();
    const u32 componentCount = m_EntityManager.GetComponentCount();
    RenderLayer::RenderImGuiDebugInfo(framerate, entityCount, componentCount);
#endif
#endif

    RenderLayer::RenderImguiFrame();

    RenderLayer::SwapBuffers(m_Window.GetGlfwWindow());
}

void Application::Cleanup()
{
    m_InputSystem.OnEndOfFrame();
}

void Application::ErrorCallback(const i32 error, const char* description)
{
    throw OpenGlException(error, description);
}
