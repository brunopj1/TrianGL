#include "Component.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Component::Component(const bool shouldUpdate)
    : Updatable(shouldUpdate)
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, Engine::Game::Component, true);
}

Component::~Component()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::Entity, Engine::Game::Component, false);
}

Entity* Component::GetParent() const
{
    return m_Parent;
}
