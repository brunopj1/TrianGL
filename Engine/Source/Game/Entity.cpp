#include "Entity.h"

using namespace Engine::Game;

Entity::Entity(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)

{}

Transform& Entity::GetTransform()
{
    return m_Transform;
}

const Transform& Entity::GetTransform() const
{
    return m_Transform;
}
