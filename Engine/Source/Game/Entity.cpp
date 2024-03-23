#include "Entity.h"

#include "Component.h"
#include "Core/EntityManager.h"

using namespace TGL;

Entity::Entity(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::EntityManager, Entity);
}

Entity::~Entity()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::EntityManager, Entity);
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
    EntityManager::DestroyEntity(this);
}

void Entity::DetachAllComponents() const
{
    while (!m_Components.empty())
    {
        m_Components.front()->Detach();
    }
}
