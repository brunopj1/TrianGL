#include "Entity.h"

#include "Component.h"
#include "Core/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, true);
}

Entity::~Entity()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, false);
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
    if (const bool isValid = Core::EntityManager::RemoveEntity(this); !isValid) return;

    DetachAllComponents();

    PREPARE_SPAWNER_USAGE();

    delete this;
}

void Entity::DetachAllComponents() const
{
    while (!m_Components.empty())
    {
        m_Components.front()->Detach();
    }
}

#ifdef DEBUG
void Entity::PrepareComponentSpawnerUsage()
{
    PREPARE_SPAWNER_USAGE_ALT(Engine::Game::Component);
}
#endif
