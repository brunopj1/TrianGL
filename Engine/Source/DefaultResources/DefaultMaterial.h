#pragma once

#include "Resources/Material.h"

namespace Engine::DefaultResources
{
    class DefaultMaterial final : public Resources::Material
    {
    private:
        Resources::TextureMaterialAttribute* m_Texture;
        Resources::Float4MaterialAttribute* m_Color;
        Resources::IntMaterialAttribute* m_IsTextureValid;

    public:
        DefaultMaterial();
        ~DefaultMaterial() override = default;

    public:
        Resources::TextureMaterialAttribute* GetTextureAttr() const;
        Resources::Float4MaterialAttribute* GetColorAttr() const;

    protected:
        void OnRenderSetup() const override;
    };
}
