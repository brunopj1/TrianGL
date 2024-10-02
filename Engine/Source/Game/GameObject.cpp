#include <Game/GameObject.h>

using namespace TGL;

GameObject::GameObject(const bool shouldUpdate, const i32 orderOfExecution)
	: m_ShouldUpdate(shouldUpdate), m_OrderOfExecution(orderOfExecution) {}

void GameObject::OnStart() {}

void GameObject::OnUpdate(const f32 deltaTime) {}
