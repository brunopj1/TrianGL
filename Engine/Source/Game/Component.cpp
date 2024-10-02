#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>

using namespace TGL;

Component::Component(const bool shouldUpdate, const i32 orderOfExecution)
	: GameObject(shouldUpdate, orderOfExecution)
{
	EXPECT_SPAWNER_USAGE_CONSTRUCTOR(TGL::EntityManager, Component);
}

Component::~Component()
{
	EXPECT_SPAWNER_USAGE_DESTRUCTOR(TGL::EntityManager, Component);
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
