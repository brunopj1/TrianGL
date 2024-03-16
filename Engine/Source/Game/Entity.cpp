#include "Entity.h"

#include "Component.h"
#include "Core/EntityManager.h"

using namespace TGL;

Entity::Entity(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::Entity);
}

Entity::~Entity()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::Entity);
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
    if (const bool isValid = EntityManager::RemoveEntity(this); !isValid) return;

    DetachAllComponents();

    PREPARE_SPAWNER_USAGE(TGL::Entity);

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
    PREPARE_SPAWNER_USAGE(TGL::Component);
}
#endif
