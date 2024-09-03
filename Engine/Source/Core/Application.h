#pragma once

#include "Exceptions/Core/FailedToInitializeEngineException.h"
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
		bool Vsync = true;
	};

	struct ServiceCollection
	{
		Clock* Clock = nullptr;
		Window* Window = nullptr;
		InputSystem* InputSystem = nullptr;
		EntityManager* EntityManager = nullptr;
		AssetManager* AssetManager = nullptr;
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
#ifndef TESTING
		template <SpawnableGameMode T, typename... Args>
		static void Run(const ApplicationConfig& config, Args&&... args);
#else
		template <SpawnableGameMode T, typename... Args>
		static void Run(const ApplicationConfig& config, const ServiceCollection& mockServiceCollection = {}, Args&&... args);
#endif

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
#ifndef TESTING
	template <SpawnableGameMode T, typename... Args>
	void Application::Run(const ApplicationConfig& config, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		// Check if the game is already running
		if (s_Running)
		{
			throw FailedToInitializeEngineException("Cannot run multiple instances of the engine at the same time");
		}

		// Create the services
		ServiceCollection serviceCollection;

		Clock clockService;
		serviceCollection.Clock = &clockService;

		Window windowService;
		serviceCollection.Window = &windowService;

		InputSystem inputSystemService;
		serviceCollection.InputSystem = &inputSystemService;

		EntityManager entityManagerService;
		serviceCollection.EntityManager = &entityManagerService;

		AssetManager assetManagerService;
		serviceCollection.AssetManager = &assetManagerService;

		// Create the application
		Application application(serviceCollection);

		// Initialize the application
		application.Init(config);

		// Create the GameMode
		GameMode* gameMode = application.m_EntityManager->CreateGameMode<T>(std::forward<Args>(args)...);

		// Run the game loop
		application.GameLoop(gameMode);

		// Terminate the application
		application.Terminate();
	}
#else
	template <SpawnableGameMode T, typename... Args>
	void Application::Run(const ApplicationConfig& config, const ServiceCollection& mockServiceCollection, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		// Check if the game is already running
		if (s_Running)
		{
			throw FailedToInitializeEngineException("Cannot run multiple instances of the engine at the same time");
		}

		// Create the services
		ServiceCollection serviceCollection = {mockServiceCollection};

		if (mockServiceCollection.Clock == nullptr)
		{
			serviceCollection.Clock = new Clock();
		}
		if (mockServiceCollection.Window == nullptr)
		{
			serviceCollection.Window = new Window();
		}
		if (mockServiceCollection.InputSystem == nullptr)
		{
			serviceCollection.InputSystem = new InputSystem();
		}
		if (mockServiceCollection.EntityManager == nullptr)
		{
			serviceCollection.EntityManager = new EntityManager();
		}
		if (mockServiceCollection.AssetManager == nullptr)
		{
			serviceCollection.AssetManager = new AssetManager();
		}

		// Create the application
		Application application(serviceCollection);

		// Initialize the application
		application.Init(config);

		// Create the GameMode
		GameMode* gameMode = application.m_EntityManager->CreateGameMode<T>(std::forward<Args>(args)...);

		// Run the game loop
		application.GameLoop(gameMode);

		// Terminate the application
		application.Terminate();

		// Delete the default services
		if (mockServiceCollection.Clock == nullptr)
		{
			delete serviceCollection.Clock; // NOLINT(readability-delete-null-pointer)
		}
		if (mockServiceCollection.Window == nullptr)
		{
			delete serviceCollection.Window; // NOLINT(readability-delete-null-pointer)
		}
		if (mockServiceCollection.InputSystem == nullptr)
		{
			delete serviceCollection.InputSystem; // NOLINT(readability-delete-null-pointer)
		}
		if (mockServiceCollection.EntityManager == nullptr)
		{
			delete serviceCollection.EntityManager; // NOLINT(readability-delete-null-pointer)
		}
		if (mockServiceCollection.AssetManager == nullptr)
		{
			delete serviceCollection.AssetManager; // NOLINT(readability-delete-null-pointer)
		}
	}
#endif
}
