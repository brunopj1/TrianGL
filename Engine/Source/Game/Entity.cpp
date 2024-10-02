#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>
#include <Game/Entity.h>

using namespace TGL;

Entity::Entity(const bool shouldUpdate, const i32 orderOfExecution)
	: GameObject(shouldUpdate, orderOfExecution)
{
	EXPECT_SPAWNER_USAGE_CONSTRUCTOR(TGL::EntityManager, Entity);
}

Entity::~Entity()
{
	EXPECT_SPAWNER_USAGE_DESTRUCTOR(TGL::EntityManager, Entity);
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
	EntityManager& entityManager = EntityManager::Get();
	entityManager.DestroyEntity(this);
}

void Entity::DetachAllComponents() const
{
	while (!m_Components.empty())
	{
		m_Components.front()->Detach();
	}
}
