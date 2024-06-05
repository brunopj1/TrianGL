#pragma once

#include <Game/GameMode.h>
#include <Core/AssetManager.h>
#include <Core/EntityManager.h>
#include <Core/InputSystem.h>

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
    private:
        friend class RandomNumberGenerator;
        
    public:
        Application(const ApplicationConfig& config = {});
        ~Application();

    public:
        void Run();

    private:
        static void Init(const ApplicationConfig& config);
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
        [[noreturn]] static void ErrorCallback(int error, const char* description);

    public:
        template <SpawnableGameMode T, typename... Args>
        void SetGameMode(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            EntityManager::CreateGameMode<T>(std::forward<Args>(args)...);
        }
    };
}
