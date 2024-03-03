#include "Component.h"

using namespace Engine::Game;

Component::Component(const bool shouldUpdate)
    : IUpdatable(shouldUpdate)
{}

Entity* Component::GetParent() const
{
    return m_Parent;
}
