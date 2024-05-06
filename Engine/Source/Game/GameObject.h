#pragma once

#include <Core/EntityManager.h>
#include <Internal/Concepts/EntitySystemConcepts.h>
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
    
    template <CastableGameObject To, CastableGameObject From>
    To* CastTo(From* object)
    {
        if (object == nullptr) return nullptr;
        
        if constexpr (std::is_base_of_v<To, From>)
        {
            return static_cast<To*>(object);
        }
        else if constexpr (std::is_base_of_v<From, To>)
        {
            return dynamic_cast<To*>(object);
        }
        else
        {
            return nullptr;
        }
    }
}
