#include "GameObject.h"

using namespace TGL;

GameObject::GameObject(const bool shouldUpdate)
    : m_ShouldUpdate(shouldUpdate)
{}

int GameObject::GetOrderOfExecution() const
{
    return 0;
}

void GameObject::OnStart()
{}

void GameObject::OnUpdate(const float deltaTime)
{}
