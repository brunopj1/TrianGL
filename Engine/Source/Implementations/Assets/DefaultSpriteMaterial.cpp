#include <Implementations/Assets/DefaultSpriteMaterial.h>

using namespace TGL;

DefaultSpriteMaterial::DefaultSpriteMaterial()
    : Material("Assets/_Engine/Shaders/default_sprite.vert", "Assets/_Engine/Shaders/default_sprite.frag")
{
    Sprite->Value = nullptr;
    Color->Value = {1.0f, 1.0f, 1.0f, 1.0f};
    IsSpriteValid->Value = 0;
}

void DefaultSpriteMaterial::OnRenderSetup() const
{
    IsSpriteValid->Value = Sprite->Value != nullptr ? 1 : 0;
}
