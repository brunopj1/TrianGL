#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <Core/Application.h>
#include <Core/Services/Public/Clock.h>
#include <Core/Services/Public/Window.h>
#include <Exceptions/OpenGL/OpenGlException.h>
#include <Game/GameMode.h>
#include <General/Camera.h>
#include <Rendering/SpriteRenderer.h>

using namespace TGL;

Application::Application(const ServiceCollection& serviceCollection)
	: m_Clock(*serviceCollection.ClockImpl),
	  m_Window(*serviceCollection.WindowImpl),
	  m_InputSystem(*serviceCollection.InputSystemImpl),
	  m_EntityManager(*serviceCollection.EntityManagerImpl),
	  m_AssetManager(*serviceCollection.AssetManagerImpl),
	  m_RenderBackend(*serviceCollection.RenderBackendImpl),
	  m_InputBackend(*serviceCollection.InputBackendImpl),
	  m_AudioBackend(*serviceCollection.AudioBackendImpl)
{
	s_Running = true;
}

Application::~Application()
{
	s_Running = false;
}

void Application::Init(const ApplicationConfig& config) // NOLINT(CppMemberFunctionMayBeConst)
{
	// Init GLFW, GLAD, IMGUI
	m_RenderBackend.SetErrorCallback(ErrorCallback);

	if (!m_RenderBackend.InitGlfw())
	{
		throw FailedToInitializeEngineException("Failed to init GLFW");
	}

	m_RenderBackend.SetupOpenGlVersion(4, 3, true);

	const auto windowPtr = m_Window.Init(config.WindowTitle, config.WindowPosition, config.WindowResolution, config.Fullscreen, config.Vsync);

	if (!m_RenderBackend.InitGlad())
	{
		throw FailedToInitializeEngineException("Failed to init Glad");
	}

	if (!m_RenderBackend.InitImgui(windowPtr))
	{
		throw FailedToInitializeEngineException("Failed to init Imgui");
	}

	m_RenderBackend.DebugVersions();

	// OpenGL settings
	m_RenderBackend.SetupOpenGlSettings();

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
	while (!m_Window.IsClosing())
	{
		m_Clock.Update();

		m_InputSystem.PollEvents();

		NewFrame();

		Cleanup();
	}
}

void Application::Terminate() // NOLINT(CppMemberFunctionMayBeConst)
{
	// Private services
	m_EntityManager.Terminate();
	m_AssetManager.Terminate();

	m_RenderBackend.TerminateImgui();

	m_Window.Terminate();

	m_RenderBackend.TerminateGlfw();
}

void Application::NewFrame() // NOLINT(CppMemberFunctionMayBeConst)
{
	m_RenderBackend.PrepareImguiFrame();

	// Get the delta time

	const f32 deltaTime = m_Clock.GetDeltaTime();

	// Update

	m_EntityManager.Update(deltaTime);

	// Render

	Camera* camera = Camera::GetMainCamera();
	if (camera != nullptr)
	{
		camera->UpdateMatrices();
	}

	const glm::vec3 backgroundColor = camera != nullptr ? camera->GetBackgroundColor() : glm::vec3(0.0f);
	m_RenderBackend.ClearBuffers(backgroundColor);

	if (camera != nullptr)
	{
		m_EntityManager.Render();
	}

#ifdef DEBUG
#ifdef IMGUI
	const u32 framerate = m_Clock.GetFrameRate();
	const u32 entityCount = m_EntityManager.GetEntityCount();
	const u32 componentCount = m_EntityManager.GetComponentCount();
	m_RenderBackend.RenderImGuiDebugInfo(framerate, entityCount, componentCount);
#endif
#endif

	m_RenderBackend.RenderImguiFrame();

	m_RenderBackend.SwapBuffers(m_Window.GetGlfwWindow());
}

void Application::Cleanup() // NOLINT(CppMemberFunctionMayBeConst)
{
	m_InputSystem.OnEndOfFrame();
}

void Application::ErrorCallback(const i32 error, const char* description)
{
	throw OpenGlException(error, description);
}
