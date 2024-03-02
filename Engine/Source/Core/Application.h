#pragma once

#include "Window.h"
#include "EntityManager.h"
#include "Exceptions/Core/GameModeAlreadySetException.h"

// Forward declarations
namespace Engine::Game
{
    class GameMode;
}

namespace Engine::Core
{
    class Application final
    {
    private:
        // TODO pass the window parameters as arguments
        Window m_Window{"TrianGL", 1600, 900, true};

        EntityManager m_EntityManager;

    public:
        Application();
        ~Application();

    public:
        void Run();

    private:
        void Init();
        void Loop();
        void Update();
        void Render();
        void Terminate();

    public:
        template <typename T>
        void SetGameMode()
        {
            m_EntityManager.InstantiateGameMode<T>();
        }
    };
}
