#include "Entity.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::Entity, true);
}

Entity::~Entity()
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::Entity, false);
}

Transform& Entity::GetTransform()
{
    return m_Transform;
}

const Transform& Entity::GetTransform() const
{
    return m_Transform;
}

const std::vector<Component*>& Entity::GetComponents() const
{
    return m_Components;
}
