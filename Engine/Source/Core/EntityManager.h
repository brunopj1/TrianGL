#pragma once

#include "DataTypes.h"
#include <Exceptions/Game/GameModeAlreadySpecifiedException.h>
#include <vector>
#include <unordered_map>

#include <Internal/Concepts/SmartPointerConcepts.h>
#include <Internal/Concepts/EntitySystemConcepts.h>
#include <Internal/Asserts/ApplicationAsserts.h>
#include <Internal/Asserts/SpawnerAsserts.h>
#include <ranges>

namespace TGL
{
    class EntityManager final
    {
    private:
        friend class Application;
        friend class RenderLayer;
        friend class GameObject;
        friend class GameMode;
        friend class Entity;
        friend class Component;
        friend class Renderable;

        template <LazyPointerValue T>
        friend class LazyPtr;

    private:
        DECLARE_SPAWNER_ASSERT_VAR(GameMode);
        DECLARE_SPAWNER_ASSERT_VAR(Entity);
        DECLARE_SPAWNER_ASSERT_VAR(Component);

    private:
        static inline u64 s_NextId;

    private:
        static inline GameMode* s_GameMode = nullptr;

        static inline std::unordered_map<u64, Entity*> s_Entities;
        static inline std::unordered_map<u64, Component*> s_Components;

        static inline std::vector<GameObject*> s_OnUpdateQueue;
        static inline std::vector<GameObject*> s_OnStartQueue;

        static inline std::vector<Renderable*> s_RenderQueue;

    public:
        EntityManager() = delete;
        ~EntityManager() = delete;

    private:
        static void Init();
        static void Terminate();

    private:
        static void Update(f32 deltaTime);
        static void Render();

    private:
        static GameMode* GetGameMode();
        static Entity* GetEntity(u64 id);
        static Component* GetComponent(u64 id);

        static u32 GetEntityCount();
        static u32 GetComponentCount();

    private:
        static void AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue);
        static void AddToRenderQueue(Renderable* renderable, std::vector<Renderable*>& queue);

    private:
        static void StoreObjectCallbacks(GameObject* object);
        static void RemoveObjectCallbacks(GameObject* object);

    private:
        static void UpdateRenderableOrder(Renderable* renderable);

    private:
        // This cannot be executed directly because of circular dependencies
        static void SetupEntityComponentRelationship(Entity* entity, Component* component);

    private:
        template <typename T, typename... Args> requires SpawnableGameMode<T, Args...>
        static T* CreateGameMode(Args&&... args);

        static void DestroyGameMode();

        template <typename T, typename... Args> requires SpawnableEntity<T, Args...>
        static T* CreateEntity(Args&&... args);

        static void DestroyEntity(Entity* entity);

        template <typename T, typename... Args> requires SpawnableComponent<T, Args...>
        static T* CreateComponent(Entity* parent, Args&&... args);

        static void DestroyComponent(Component* component);

    private:
        template <SearchableEntity T>
        static T* FindEntityGlobally();

        template <SearchableEntity T>
        static std::vector<T*> FindEntitiesGlobally();

        template <SearchableComponent T>
        static T* FindComponentGlobally();

        template <SearchableComponent T>
        static std::vector<T*> FindComponentsGlobally();

        template <SearchableComponent T>
        static T* FindComponentInEntity(const std::vector<Component*>& entityComponents);

        template <SearchableComponent T>
        static std::vector<T*> FindComponentsInEntity(const std::vector<Component*>& entityComponents);
    };

    // Template definitions

    template <typename T, typename... Args> requires SpawnableGameMode<T, Args...>
    T* EntityManager::CreateGameMode(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        ASSERT_APPLICATION_OBJECT_CREATION();

        if (s_GameMode != nullptr) throw GameModeAlreadySpecifiedException();

        PREPARE_SPAWNER_ASSERT(GameMode);

        T* instance = new T(std::forward<Args>(args)...);

        instance->m_Id = s_NextId++;

        s_GameMode = instance;

        StoreObjectCallbacks(instance);

        return instance;
    }

    template <typename T, typename... Args> requires SpawnableEntity<T, Args...>
    T* EntityManager::CreateEntity(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward) 
    {
        ASSERT_APPLICATION_OBJECT_CREATION();

        PREPARE_SPAWNER_ASSERT(Entity);

        T* instance = new T(std::forward<Args>(args)...);

        instance->m_Id = s_NextId++;

        s_Entities.emplace(instance->m_Id, instance);

        StoreObjectCallbacks(instance);

        return instance;
    }

    template <typename T, typename... Args> requires SpawnableComponent<T, Args...>
    T* EntityManager::CreateComponent(Entity* parent, Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        ASSERT_APPLICATION_OBJECT_CREATION();

        PREPARE_SPAWNER_ASSERT(Component);

        T* instance = new T(std::forward<Args>(args)...);

        instance->m_Id = s_NextId++;

        s_Components.emplace(instance->m_Id, instance);

        StoreObjectCallbacks(instance);

        SetupEntityComponentRelationship(parent, instance);

        return instance;
    }

    template <SearchableEntity T>
    T* EntityManager::FindEntityGlobally()
    {
        for (auto entity : s_Entities)
        {
            if (T* casted = dynamic_cast<T*>(entity))
            {
                return casted;
            }
        }

        return nullptr;
    }

    template <SearchableEntity T>
    std::vector<T*> EntityManager::FindEntitiesGlobally()
    {
        std::vector<T*> entities;

        for (auto entity : s_Entities | std::views::values)
        {
            if (T* casted = dynamic_cast<T*>(entity))
            {
                entities.push_back(casted);
            }
        }

        return entities;
    }

    template <SearchableComponent T>
    T* EntityManager::FindComponentGlobally()
    {
        for (auto component : s_Components | std::views::values)
        {
            if (T* casted = dynamic_cast<T*>(component))
            {
                return casted;
            }
        }

        return nullptr;
    }

    template <SearchableComponent T>
    std::vector<T*> EntityManager::FindComponentsGlobally()
    {
        std::vector<T*> components;

        for (auto component : s_Components)
        {
            if (T* casted = dynamic_cast<T*>(component))
            {
                components.push_back(casted);
            }
        }

        return components;
    }

    template <SearchableComponent T>
    T* EntityManager::FindComponentInEntity(const std::vector<Component*>& entityComponents)
    {
        for (auto component : entityComponents)
        {
            if (T* casted = dynamic_cast<T*>(component))
            {
                return casted;
            }
        }

        return nullptr;
    }

    template <SearchableComponent T>
    std::vector<T*> EntityManager::FindComponentsInEntity(const std::vector<Component*>& entityComponents)
    {
        std::vector<T*> components;

        for (auto component : entityComponents)
        {
            if (T* casted = dynamic_cast<T*>(component))
            {
                components.push_back(casted);
            }
        }

        return components;
    }
}
