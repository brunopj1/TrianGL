#include <Core/Services/Private/EntityManager.h>
#include <Game/Internal/Renderable.h>

using namespace TGL;

Transform& Renderable::GetTransform()
{
	return m_Transform;
}

const Transform& Renderable::GetTransform() const
{
	return m_Transform;
}

i32 Renderable::GetZIndex() const
{
	return m_ZIndex;
}

void Renderable::SetZIndex(const i32 zIndex)
{
	if (zIndex == m_ZIndex)
	{
		return;
	}

	m_ZIndex = zIndex;

	EntityManager& entityManager = EntityManager::Get();
	entityManager.UpdateRenderableOrder(this);
}
