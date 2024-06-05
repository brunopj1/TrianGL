#include <Game/Rendering/Renderable.h>

#include <Core/EntityManager.h>

using namespace TGL;

int Renderable::GetZIndex() const
{
    return m_ZIndex;
}

void Renderable::SetZIndex(const int zIndex)
{
    const bool valueChanged = m_ZIndex != zIndex;

    m_ZIndex = zIndex;

    if (valueChanged)
    {
        EntityManager::UpdateRenderableOrder(this);
    }
}
