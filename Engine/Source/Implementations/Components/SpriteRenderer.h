#pragma once

#include <Game/Component.h>
#include <Game/Rendering/Renderable.h>
#include <Memory/SharedPtr.h>

#include <Implementations/Assets/DefaultSpriteMaterial.h>

namespace TGL
{
    // Forward declarations
    class Material;

    class SpriteRenderer final : public Component, public Renderable
    {
    private:
        friend class Application;
        
    private:
        Transform m_Transform;
        SharedPtr<Material> m_Material = nullptr;
        glm::vec2 m_Pivot = glm::vec2(0.5f);
        glm::bvec2 m_Flip = glm::bvec2(false);

    public:
        SpriteRenderer(SharedPtr<Material> material = nullptr);
        ~SpriteRenderer() override = default;

    public:
        Transform& GetTransform();
        const Transform& GetTransform() const;
        
        SharedPtr<Material> GetMaterial() const;
        void SetMaterial(SharedPtr<Material> material);
        SharedPtr<DefaultSpriteMaterial> UseDefaultMaterial();

        glm::vec2 GetPivot() const;
        void SetPivot(const glm::vec2& pivot);

    private:
        void Render() const override;
    };
}
