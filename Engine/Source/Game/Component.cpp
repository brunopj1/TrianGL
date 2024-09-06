#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>

using namespace TGL;

Component::Component(const bool shouldUpdate)
	: GameObject(shouldUpdate)
{
	ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::EntityManager, Component);
}

Component::~Component()
{
	ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::EntityManager, Component);
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
