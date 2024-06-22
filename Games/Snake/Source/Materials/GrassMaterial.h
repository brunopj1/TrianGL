#pragma once

#include "Assets/Material.h"

class GrassMaterial final : public TGL::Material
{
public:
    TGL::FloatUniform* const Seed = AddUniform<TGL::FloatUniform>("uSeed");
    TGL::Uint2Uniform* const GridSize = AddUniform<TGL::Uint2Uniform>("uGridSize");
    TGL::SpriteUniform* const SpriteSheet = AddUniform<TGL::SpriteUniform>("uSpriteSheet");
    TGL::SpriteUniform* const SpriteGrassNormal = AddUniform<TGL::SpriteUniform>("uSpriteGrassNormal");
    TGL::SpriteUniform* const SpriteGrassTall = AddUniform<TGL::SpriteUniform>("uSpriteGrassTall");
    TGL::SpriteUniform* const SpriteGrassFlowers = AddUniform<TGL::SpriteUniform>("uSpriteGrassFlowers");
    TGL::SpriteUniform* const SpriteGrassRocks = AddUniform<TGL::SpriteUniform>("uSpriteGrassRocks");
    
public:
    GrassMaterial();
};
