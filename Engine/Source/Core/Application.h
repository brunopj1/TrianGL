#pragma once

#include "Window.h"
#include "EntityManager.h"

// TODO check if I can prevent the forward declarations from being included in the header

// Forward declarations
namespace Engine::Game
{
    class GameMode;
}

namespace Engine::Core
{
    struct ApplicationConfig
    {
        std::string Title = "TrianGL";
        glm::uvec2 Resolution = {1600, 900};
        bool Vsync = true;
    };

    class Application final
    {
    private:
        Window m_Window;
        EntityManager m_EntityManager;

    public:
        Application(const ApplicationConfig& config = {});
        ~Application();

    private:
        void Init();
        void Terminate();

    public:
        void Run();

    private:
        void Update();
        void Render() const;
        void PollEvents() const;

    public:
        template <typename T>
        void SetGameMode()
        {
            m_EntityManager.CreateGameMode<T>();
        }
    };
}
