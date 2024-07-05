#pragma once

namespace TGL
{
    class Renderable
    {
    private:
        friend class EntityManager;

    private:
        int m_ZIndex = 0;

    protected:
        Renderable() = default;
        virtual ~Renderable() = default;

    public:
        int GetZIndex() const;
        void SetZIndex(int zIndex);

    protected:
        virtual void Render() const = 0;
    };
}
