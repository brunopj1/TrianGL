#pragma once

#include <Game/GameObject.h>
#include <Game/Transform.h>
#include <Core/EntityManager.h>
#include <vector>

namespace TGL
{
    class Entity : public GameObject
    {
    private:
        friend class EntityManager;
        friend class Component;

    private:
        Transform m_Transform;
        std::vector<Component*> m_Components;

    protected:
        Entity(bool shouldUpdate);
        ~Entity() override;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;

    public:
        void Destroy();

    public:
        template <typename T, typename... Args> requires SpawnableComponent<T, Args...>
        T* AttachComponent(Args&&... args);

        void DetachAllComponents() const;

    public:
        template <SearchableComponent T>
        T* FindComponent();

        template <SearchableComponent T>
        std::vector<T*> FindComponents();
    };

    // Template definitions

    template <typename T, typename... Args> requires SpawnableComponent<T, Args...>
    T* Entity::AttachComponent(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        return EntityManager::CreateComponent<T>(this, std::forward<Args>(args)...);
    }

    template <SearchableComponent T>
    T* Entity::FindComponent()
    {
        return EntityManager::FindComponentInEntity<T>(m_Components);
    }

    template <SearchableComponent T>
    std::vector<T*> Entity::FindComponents()
    {
        return EntityManager::FindComponentsInEntity<T>(m_Components);
    }
}
