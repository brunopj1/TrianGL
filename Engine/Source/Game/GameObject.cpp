#include <Game/GameObject.h>

using namespace TGL;

u64 GameObject::GetId() const
{
	return m_Id;
}

GameObject::GameObject(const bool shouldUpdate, const i32 orderOfExecution)
	: m_Id(EntityManager::Get().GetNextId()), m_ShouldUpdate(shouldUpdate), m_OrderOfExecution(orderOfExecution)
{}

void GameObject::OnStart() {}

void GameObject::OnUpdate(const f32 deltaTime) {}
