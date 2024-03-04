#pragma once

#include "Window.h"
#include "EntityManager.h"
#include "InputSystem.h"

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
        InputSystem m_InputSystem;

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

    private:
        [[noreturn]] static void ErrorCallback(int error, const char* description);

    public:
        template <typename T>
        void SetGameMode() const
        {
            m_EntityManager.CreateGameMode<T>();
        }
    };
}
