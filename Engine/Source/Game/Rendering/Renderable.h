#pragma once
#include "Core/DataTypes.h"

namespace TGL
{
    class Renderable
    {
    private:
        friend class EntityManager;

    private:
        i32 m_ZIndex = 0;

    protected:
        Renderable() = default;
        virtual ~Renderable() = default;

    public:
        i32 GetZIndex() const;
        void SetZIndex(i32 zIndex);

    protected:
        virtual void Render() const = 0;
    };
}
