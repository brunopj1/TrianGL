#include "DefaultMaterial.h"

using namespace TGL;

DefaultMaterial::DefaultMaterial()
    : Material("Assets/_Engine/Shaders/default.vert", "Assets/_Engine/Shaders/default.frag", true),
      Texture(AddUniform<TextureUniform>("uTexture")),
      Color(AddUniform<Float4Uniform>("uColor")),
      IsTextureValid(AddUniform<IntUniform>("uIsTextureValid"))
{
    Texture->Value = nullptr;
    Color->Value = {1.0f, 1.0f, 1.0f, 1.0f};
    IsTextureValid->Value = 0;
}

void DefaultMaterial::OnRenderSetup() const
{
    IsTextureValid->Value = Texture->Value != nullptr ? 1 : 0;
}
