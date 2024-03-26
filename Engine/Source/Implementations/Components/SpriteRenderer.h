#pragma once

#include "Game/Component.h"
#include "Game/Rendering/Renderable.h"
#include <memory>

namespace TGL
{
    // Forward declarations
    class Material;
    class DefaultMaterial;

    class SpriteRenderer final : public Component, public Renderable
    {
    private:
        friend class Application;

    private:
        static inline unsigned int s_QuadVao = 0;
        static inline unsigned int s_QuadVbo = 0;
        static inline unsigned int s_QuadEbo = 0;

    private:
        std::shared_ptr<Material> m_Material = nullptr;
        glm::vec2 m_Pivot = glm::vec2(0.5f);
        glm::bvec2 m_Flip = glm::bvec2(false);

    public:
        SpriteRenderer(std::shared_ptr<Material> material = nullptr);
        ~SpriteRenderer() override = default;

    public:
        std::shared_ptr<Material> GetMaterial() const;
        void SetMaterial(std::shared_ptr<Material> material);
        std::shared_ptr<DefaultMaterial> UseDefaultMaterial();

        glm::vec2 GetPivot() const;
        void SetPivot(const glm::vec2& pivot);

    private:
        static void Init();
        static void Terminate();

    private:
        void Render() override;
    };
}
