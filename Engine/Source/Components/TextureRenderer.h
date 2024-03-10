#pragma once

#include "Game/Component.h"
#include "Game/Internal/Renderable.h"

namespace Engine
{
    // Forward declarations
    class Material;
    class DefaultMaterial;

    class TextureRenderer final : public Component, public Renderable
    {
    private:
        friend class Application;

    private:
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

    private:
        Material* m_Material = nullptr;

    public:
        TextureRenderer(Material* material = nullptr);
        ~TextureRenderer() override = default;

    public:
        Material* GetMaterial() const;
        void SetMaterial(Material* material, bool unloadPreviousMaterial = false);
        DefaultMaterial* UseDefaultMaterial(bool unloadPreviousMaterial = false);

    private:
        static void Init();
        static void Terminate();

    private:
        void Render() override;
    };
}
