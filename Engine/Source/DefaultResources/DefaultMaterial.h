#pragma once

#include "Resources/Material.h"

namespace Engine
{
    class DefaultMaterial final : public Material
    {
    private:
        TextureMaterialAttribute* m_Texture;
        Float4MaterialAttribute* m_Color;
        IntMaterialAttribute* m_IsTextureValid;

    public:
        DefaultMaterial();
        ~DefaultMaterial() override = default;

    public:
        TextureMaterialAttribute* GetTextureAttr() const;
        Float4MaterialAttribute* GetColorAttr() const;

    protected:
        void OnRenderSetup() const override;
    };
}
