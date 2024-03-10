﻿#pragma once

#include "Entity.h"
#include "Exceptions/Game/GameModeAlreadySpecifiedException.hpp"
#include "Core/EntityManager.h"
#include "Util/Macros/SpawnerMacros.hpp"

namespace Engine
{
    class GameMode
    {
    private:
        friend class Application;
        friend class EntityManager;

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
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::GameMode)>
        static void CreateGameMode(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            if (GetInstance() != nullptr) throw GameModeAlreadySpecifiedException();

            PREPARE_SPAWNER_USAGE();

            T* instance = new T(std::forward<Args>(args)...);

            EntityManager::SetGameMode(instance);
        }

        void Destroy() const;

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(Engine::Entity)>
        static T* SpawnEntity(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return Entity::SpawnEntity<T>(std::forward<Args>(args)...);
        }
    };
}
