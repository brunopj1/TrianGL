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
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::Component, false);
}

Entity* Component::GetParent() const
{
    return m_Parent;
}
