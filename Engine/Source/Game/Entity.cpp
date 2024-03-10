#include "Entity.h"

#include "Component.h"
#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, Engine::Game::Entity, true);
}

Entity::~Entity()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, Engine::Game::Entity, false);
}

Transform& Entity::GetTransform()
{
    return m_Transform;
}

const Transform& Entity::GetTransform() const
{
    return m_Transform;
}

void Entity::Destroy()
{
    DetachAllComponents();

    Services::EntityManager::RemoveEntity(this);

    PREPARE_SPAWNER_USAGE();

    delete this;
}

void Entity::DetachComponent(Component* component)
{
    if (const size_t num = std::erase(m_Components, component); num == 0) return;

    Services::EntityManager::RemoveComponent(component);

    PREPARE_SPAWNER_USAGE();

    delete component;
}

void Entity::DetachComponents(const std::vector<Component*>& components)
{
    for (const auto& component : components)
    {
        DetachComponent(component);
    }
}

void Entity::DetachAllComponents()
{
    while (!m_Components.empty())
    {
        DetachComponent(m_Components.front());
    }
}
