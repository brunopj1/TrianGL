#include "Component.h"

#include "Core/EntityManager.h"

using namespace TGL;

Component::Component(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::Component);
}

Component::~Component()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::Component);
}

Entity* Component::GetParent() const
{
    return m_Parent;
}

void Component::Detach()
{
    if (const bool isValid = EntityManager::RemoveComponent(this); !isValid) return;

    std::erase(m_Parent->m_Components, this);

    PREPARE_SPAWNER_USAGE();

    delete this;
}
