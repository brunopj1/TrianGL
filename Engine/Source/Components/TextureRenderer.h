#pragma once

#include "Game/Component.h"
#include "Game/Base/Renderable.h"

namespace TGL
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
        glm::vec2 m_Pivot = glm::vec2(0.5f);

    public:
        TextureRenderer(Material* material = nullptr);
        ~TextureRenderer() override = default;

    public:
        Material* GetMaterial() const;
        void SetMaterial(Material* material, bool unloadPreviousMaterial = false);
        DefaultMaterial* UseDefaultMaterial(bool unloadPreviousMaterial = false);

        glm::vec2 GetPivot() const;
        void SetPivot(const glm::vec2& pivot);

    private:
        static void Init();
        static void Terminate();

    private:
        void Render() override;
    };
}
