#include "Entity.h"

#include "Core/EntityManager.h"
#include "Util/DebugFeatures.hpp"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::Entity");
}

Entity::~Entity()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::Entity");
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
