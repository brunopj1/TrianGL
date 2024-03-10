#include "Renderable.h"

using namespace Engine;

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
    m_ZIndex = zIndex;
}
