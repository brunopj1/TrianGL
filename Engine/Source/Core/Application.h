#pragma once

#include "Window.h"
#include "EntityManager.h"

// Forward declarations
namespace Engine::Game
{
    class GameMode;
}

namespace Engine::Core
{
    struct ApplicationConfig
    {
        // ReSharper disable CppInconsistentNaming

        std::string Title = "TrianGL";
        glm::uvec2 Resolution = {1600, 900};
        bool Vsync = true;

        // ReSharper restore CppInconsistentNaming
    };

    class Application final
    {
    private:
        Window m_Window;
        EntityManager m_EntityManager;

    public:
        Application(const ApplicationConfig& config = {});
        ~Application();

    public:
        void Run();

    private:
        void Init();
        void Update();
        void Render() const;
        void Terminate() const;

    public:
        template <typename T>
        void SetGameMode()
        {
            m_EntityManager.CreateGameMode<T>();
        }
    };
}
