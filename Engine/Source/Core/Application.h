#pragma once

#include "Core/ServiceCollection.h"
#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include "Internal/Macros/TestMacros.h"
#include "Services/Clock.h"
#include "Services/Window.h"
#include <Core/DataTypes.h>
#include <Core/Services/InputSystem.h>
#include <Core/Services/Internal/AssetManager.h>
#include <Core/Services/Internal/EntityManager.h>

// TODO ensure that all const methods return pointer to const data

namespace TGL
{
	struct ApplicationConfig
	{
		std::string WindowTitle = "TrianGL";
		glm::ivec2 WindowPosition = {50, 50};
		glm::uvec2 WindowResolution = {1280, 720};
		bool Fullscreen = false;
		bool Vsync = false;
	};

	struct RunDetails
	{
		f32 Duration = 0.0f;
		u32 FrameCount = 0;
	};

	class Application
	{
	private:
		static inline bool s_Running = false;

	private:
		Clock* m_Clock;
		Window* m_Window;
		InputSystem* m_InputSystem;
		EntityManager* m_EntityManager;
		AssetManager* m_AssetManager;

	private:
		Application(const ServiceCollection& serviceCollection);
		~Application();

	public:
		DELETE_COPY_AND_MOVE_CONSTRUCTORS(Application);

	public:
		template <SpawnableGameMode T, typename... Args>
		static RunDetails Run(const ApplicationConfig& config, Args&&... args);

		TEST_RUN_PRIVACY()
		template <SpawnableGameMode T, typename... Args>
		static RunDetails Run(const ApplicationConfig& config, ServiceCollection& serviceCollection, Args&&... args);


	private:
		void Init(const ApplicationConfig& config);
		void Terminate();

	private:
		void GameLoop(GameMode* gameMode);

	private:
		void NewFrame();
		void Cleanup();

	private:
		[[noreturn]] static void ErrorCallback(i32 error, const char* description);
	};

	// Template definitions

	template <SpawnableGameMode T, typename... Args>
	RunDetails Application::Run(const ApplicationConfig& config, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		ServiceCollection serviceCollection;
		return Run<T>(config, serviceCollection, std::forward<Args>(args)...);
	}

	template <SpawnableGameMode T, typename... Args>
	RunDetails Application::Run(const ApplicationConfig& config, ServiceCollection& serviceCollection, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		// Check if the game is already running
		if (s_Running)
		{
			throw FailedToInitializeEngineException("Cannot run multiple instances of the engine at the same time");
		}

		// Create the public services
		serviceCollection.CreateService<Clock>();
		serviceCollection.CreateService<Window>();
		serviceCollection.CreateService<InputSystem>();

		// Create the private services
		serviceCollection.CreateService<EntityManager>();
		serviceCollection.CreateService<AssetManager>();

		// Create the application
		Application application(serviceCollection);

		// Initialize the application
		application.Init(config);

		// Create the GameMode
		GameMode* gameMode = application.m_EntityManager->CreateGameMode<T>(std::forward<Args>(args)...);

		// Run the game loop
		application.GameLoop(gameMode);

		// Get the run details
		RunDetails details;
		details.Duration = application.m_Clock->GetTotalTime();
		details.FrameCount = application.m_Clock->GetFrameCount();

		// Terminate the application
		application.Terminate();

		// Return the duration of the game loop
		return details;
	}
}
