#pragma once

#include "DataTypes.h"
#include <Game/GameMode.h>
#include <Core/AssetManager.h>
#include <Core/EntityManager.h>
#include <Core/InputSystem.h>
#include "Exceptions/Core/CannotRunEngine.h"

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

    class Application final
    {
    public:
        Application(const ApplicationConfig& config = {});
        ~Application();

    public:
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

    public:
        template <SpawnableGameMode T, typename... Args>
        void Run(Args&&... args);

    private:
        static void Init(const ApplicationConfig& config);
        static void GameLoop(GameMode* gameMode);
        static void Terminate();

    private:
        static void NewFrame();
        static void Cleanup();
        static void PollEvents();

#ifdef DEBUG

    private:
        static void RenderDebugInfo();

#endif

    private:
        [[noreturn]] static void ErrorCallback(i32 error, const char* description);
    };

    // Template definitions

    template <SpawnableGameMode T, typename... Args>
    void Application::Run(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        // Check and update the status
        const auto appStatus = ApplicationStatus::GetStatus();

        if (appStatus != ApplicationStatusValue::PostInit)
        {
            throw CannotRunEngine();
        }

        ApplicationStatus::SetStatus(ApplicationStatusValue::Running);

        // Create the GameMode
        GameMode* gameMode = EntityManager::CreateGameMode<T>(std::forward<Args>(args)...);

        // Run the game loop
        GameLoop(gameMode);

        // Update the status
        ApplicationStatus::SetStatus(ApplicationStatusValue::PostRun);
    }
}
