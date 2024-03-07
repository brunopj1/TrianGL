#include "Entity.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, "Engine::Game::Entity");
}

Entity::~Entity()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, "Engine::Game::Entity");
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
