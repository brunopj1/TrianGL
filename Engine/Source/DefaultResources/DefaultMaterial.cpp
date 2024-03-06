#include "DefaultMaterial.h"

using namespace Engine::DefaultResources;

DefaultMaterial::DefaultMaterial()
    : Material("Assets/_Engine/Shaders/default.vert", "Assets/_Engine/Shaders/default.frag", true)
{
    m_Texture = AddTextureAttribute("uTexture", 0);

    m_Color = AddAttribute<Resources::Float4MaterialAttribute>("uColor");
    m_Color->SetValue({1.0f, 1.0f, 1.0f, 1.0f});

    m_IsTextureValid = AddAttribute<Resources::IntMaterialAttribute>("uIsTextureValid");
}

Engine::Resources::TextureMaterialAttribute* DefaultMaterial::GetTextureAttr() const
{
    return m_Texture;
}

Engine::Resources::Float4MaterialAttribute* DefaultMaterial::GetColorAttr() const
{
    return m_Color;
}

void DefaultMaterial::OnRenderSetup() const
{
    m_IsTextureValid->SetValue(m_Texture->GetValue() != nullptr ? 1 : 0);
}
