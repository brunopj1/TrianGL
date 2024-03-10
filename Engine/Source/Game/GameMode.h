#pragma once
#include "Exceptions/Game/GameModeAlreadySpecifiedException.hpp"
#include "Core/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"
#include <type_traits>

// Forward declarations
namespace Engine::Core
{
    class Application;
    class EntityManager;
}

namespace Engine::Game
{
    class GameMode
    {
    private:
        friend class Core::Application;
        friend class Core::EntityManager;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    public:
        GameMode();
        virtual ~GameMode();

    public:
        virtual void OnStart();
        virtual void OnEarlyUpdate(float deltaTime);
        virtual void OnLateUpdate(float deltaTime);

    public:
        static GameMode* GetInstance();

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<GameMode, T>>>
        T* As()
        {
            return dynamic_cast<T*>(this);
        }

    private:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Game::GameMode)>
        static void CreateGameMode(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            if (GetInstance() != nullptr) throw Exceptions::Game::GameModeAlreadySpecifiedException();

            PREPARE_SPAWNER_USAGE();

            T* instance = new T(std::forward<Args>(args)...);

            Core::EntityManager::SetGameMode(instance);
        }

        void Destroy() const;

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Game::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return Entity::SpawnEntity<T>(std::forward<Args>(args)...);
        }
    };
}
