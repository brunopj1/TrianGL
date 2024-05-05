#pragma once

#include "Core/EntityManager.h"
#include "Util/Concepts/SmartPointerConcepts.h"
#include <cstdint>

namespace TGL
{
    class GameObject
    {
    private:
        friend class EntityManager;

        template <LazyPointerValue T>
        friend class LazyPtr;

    private:
        uint64_t m_Id = 0;
        bool m_ShouldUpdate;

    protected:
        GameObject(bool shouldUpdate);
        virtual ~GameObject() = default;

    protected:
        virtual int GetOrderOfExecution() const;

    protected:
        virtual void OnStart();
        virtual void OnUpdate(float deltaTime);

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
        T* CastTo()
        {
            return dynamic_cast<T*>(this);
        }

    public:
        template <typename T, typename... Args>
        requires SpawnableEntity<T, Args...>
        static T* SpawnEntity(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            return EntityManager::CreateEntity<T>(std::forward<Args>(args)...);
        }

    public:
        template <SearchableEntity T>
        static T* FindEntityGlobally()
        {
            return EntityManager::FindEntityGlobally<T>();
        }

        template <SearchableEntity T>
        static std::vector<T*> FindEntitiesGlobally()
        {
            return EntityManager::FindEntitiesGlobally<T>();
        }


        template <SearchableComponent T>
        static T* FindComponentGlobally()
        {
            return EntityManager::FindComponentGlobally<T>();
        }

        template <SearchableComponent T>
        static std::vector<T*> FindComponentsGlobally()
        {
            return EntityManager::FindComponentsGlobally<T>();
        }
    };
}
