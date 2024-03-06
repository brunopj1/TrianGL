#include "Component.h"

#include "Core/EntityManager.h"
#include "Util/DebugFeatures.hpp"

using namespace Engine::Game;

Component::Component(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::Component");
}

Component::~Component()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::Component");
}

Entity* Component::GetParent() const
{
    return m_Parent;
}
