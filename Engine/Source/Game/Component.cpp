#include "Component.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

Component::Component(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::Component, true);
}

Component::~Component()
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::Component, false);
}

Entity* Component::GetParent() const
{
    return m_Parent;
}
