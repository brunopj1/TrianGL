#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>

using namespace TGL;

Component::Component(const bool shouldUpdate, const i32 orderOfExecution)
	: GameObject(shouldUpdate, orderOfExecution)
{
	ASSERT_ENTITY_FACTORY_CONSTRUCTOR(Component);
}

Component::~Component()
{
	ASSERT_ENTITY_FACTORY_DESTRUCTOR(Component);
}

Entity* Component::GetParent() const
{
	return m_Parent;
}

void Component::Detach()
{
	EntityManager& entityManager = EntityManager::Get();
	entityManager.DestroyComponent(this);
}
