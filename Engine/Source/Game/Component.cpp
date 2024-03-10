#include "Component.h"

#include "Core/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Component::Component(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Component, true);
}

Component::~Component()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Component, false);
}

Entity* Component::GetParent() const
{
    return m_Parent;
}

void Component::Detach()
{
    if (const bool isValid = Core::EntityManager::RemoveComponent(this); !isValid) return;

    std::erase(m_Parent->m_Components, this);

    PREPARE_SPAWNER_USAGE();

    delete this;
}
