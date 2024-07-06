﻿#include <Game/Rendering/Renderable.h>

#include <Core/EntityManager.h>

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
        EntityManager::UpdateRenderableOrder(this);
    }
}
