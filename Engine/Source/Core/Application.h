#pragma once

#include "Clock.h"
#include "DataTypes.h"
#include "Window.h"
#include "Exceptions/Core/FailedToInitializeEngineException.h"
#include <Game/GameMode.h>
#include <Core/AssetManager.h>
#include <Core/EntityManager.h>
#include <Core/InputSystem.h>

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

    class Application
    {
    private:
        static inline bool s_Running = false;
        
    private:
        EntityManager m_EntityManager;
        AssetManager m_AssetManager;

    private:
        Clock m_Clock;
        Window m_Window;
        InputSystem m_InputSystem;
        
    private:
        Application(const ApplicationConfig& config);
        ~Application();

    public:
        DELETE_COPY_AND_MOVE_CONSTRUCTORS(Application);

    public:
        template <SpawnableGameMode T, typename... Args>
        static void Run(const ApplicationConfig& config, Args&&... args);

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
    void Application::Run(const ApplicationConfig& config, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        // Check if the game is already running
        if (s_Running)
        {
            throw FailedToInitializeEngineException("Cannot run multiple instances of the engine at the same time");
        }
        
        // Create the application
        Application application(config);
        
        // Create the GameMode
        GameMode* gameMode = application.m_EntityManager.CreateGameMode<T>(std::forward<Args>(args)...);

        // Run the game loop
        application.GameLoop(gameMode);
    }
}
