#include "DefaultMaterial.h"

using namespace TGL;

DefaultMaterial::DefaultMaterial()
    : Material("Assets/_Engine/Shaders/default.vert", "Assets/_Engine/Shaders/default.frag")
{
    Sprite->Value = nullptr;
    Color->Value = {1.0f, 1.0f, 1.0f, 1.0f};
    IsSpriteValid->Value = 0;
}

void DefaultMaterial::OnRenderSetup() const
{
    IsSpriteValid->Value = Sprite->Value != nullptr ? 1 : 0;
}
