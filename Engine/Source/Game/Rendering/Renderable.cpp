#include <Game/Rendering/Renderable.h>

#include <Core/EntityManager.h>

using namespace TGL;

Transform& Renderable::GetTransform()
{
    return m_Transform;
}

const Transform& Renderable::GetTransform() const
{
    return m_Transform;
}

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
