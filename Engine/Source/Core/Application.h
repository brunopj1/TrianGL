#pragma once

#include "Services/Clock.h"
#include "Services/DefaultResourcesCollection.h"
#include "Window.h"
#include "Game/GameMode.h"
#include "Services/ResourceManager.h"
#include "Services/EntityManager.h"
#include "Services/InputSystem.h"

// Forward declarations
namespace Engine::Services
{
    class EntityManager;
}

namespace Engine::Core
{
    struct ApplicationConfig
    {
        std::string WindowTitle = "TrianGL";
        glm::ivec2 WindowPosition = {0, 0};
        glm::uvec2 WindowResolution = {1280, 720};
        bool Fullscreen = false;
        bool Vsync = true;
    };

    class Application final
    {
    private:
        Window m_Window;

        Services::Clock m_Clock;

        Services::ResourceManager m_ResourceManager;
        Services::DefaultResourcesCollection m_DefaultResources;

        Services::EntityManager m_EntityManager;

        Services::InputSystem m_InputSystem;

    public:
        Application(const ApplicationConfig& config = {});
        ~Application();

    public:
        void Run();

    private:
        void Init();
        void Terminate() const;

    private:
        void Update();
        void Render() const;
        void PollEvents() const;

    private:
        [[noreturn]] static void ErrorCallback(int error, const char* description);

    public:
        template <typename T>
        void SetGameMode() const
        {
            Game::GameMode::CreateGameMode<T>();
        }
    };
}
