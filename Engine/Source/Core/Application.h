#pragma once

#include "IdGenerator.h"
#include "Core/Clock.h"
#include "Window.h"
#include "Game/GameMode.h"
#include "Core/ResourceManager.h"
#include "Core/EntityManager.h"
#include "Core/InputSystem.h"

namespace TGL
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

        Clock m_Clock;

        IdGenerator m_IdGenerator;
        ResourceManager m_ResourceManager{&m_IdGenerator};
        EntityManager m_EntityManager{&m_IdGenerator};

        InputSystem m_InputSystem;

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
        void Cleanup();
        void PollEvents() const;

    private:
        [[noreturn]] static void ErrorCallback(int error, const char* description);

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::GameMode)>
        void SetGameMode(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            GameMode::CreateGameMode<T>(std::forward<Args>(args)...);
        }
    };
}
