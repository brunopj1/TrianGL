#include "Component.h"

#include "Core/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine;

Component::Component(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE(Engine::Component, true);
}

Component::~Component()
{
    ASSERT_SPAWNER_USAGE(Engine::Component, false);
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
