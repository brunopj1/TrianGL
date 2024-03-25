#pragma once

namespace TGL
{
    class ImGuiRenderer
    {
    private:
        friend class EntityManager;

    public:
        ImGuiRenderer() = default;
        virtual ~ImGuiRenderer() = default;

#ifdef DEBUG

    protected:
        virtual void RenderImGui() = 0;

#endif
    };
}
