#include <Game/GameObject.h>

using namespace TGL;

GameObject::GameObject(const bool shouldUpdate)
    : m_ShouldUpdate(shouldUpdate)
{}

i32 GameObject::GetOrderOfExecution() const
{
    return 0;
}

void GameObject::OnStart()
{}

void GameObject::OnUpdate(const f32 deltaTime)
{}
