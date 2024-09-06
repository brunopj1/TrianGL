#include <Core/Services/Private/EntityManager.h>
#include <Game/Rendering/Renderable.h>

using namespace TGL;

i32 Renderable::GetZIndex() const
{
	return m_ZIndex;
}

void Renderable::SetZIndex(const i32 zIndex)
{
	const bool valueChanged = m_ZIndex != zIndex;

	m_ZIndex = zIndex;

	if (valueChanged)
	{
		EntityManager& entityManager = EntityManager::Get();
		entityManager.UpdateRenderableOrder(this);
	}
}
