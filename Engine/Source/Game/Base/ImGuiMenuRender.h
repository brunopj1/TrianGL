#pragma once

namespace TGL
{
    class ImGuiMenuRenderer
    {
    private:
        friend class EntityManager;

    public:
        ImGuiMenuRenderer() = default;
        virtual ~ImGuiMenuRenderer() = default;

#ifdef DEBUG

    protected:
        virtual int GetRenderOrder() const;
        virtual void RenderImGuiMenu() = 0;

#endif
    };
}
