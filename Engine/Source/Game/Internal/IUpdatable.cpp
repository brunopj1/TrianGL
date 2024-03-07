#include "IUpdatable.h"

using namespace Engine::Game::Internal;

IUpdatable::IUpdatable(const bool shouldUpdate)
    : m_ShouldUpdate(shouldUpdate)
{}

int IUpdatable::GetOrderOfExecution() const
{
    return 0;
}

void IUpdatable::OnStart() {}

void IUpdatable::OnUpdate(float deltaTime) {}
