#include "DefaultParticleMaterial.h"

using namespace TGL;

DefaultParticleMaterial::DefaultParticleMaterial()
	: Material("Assets/_Engine/Shaders/default_particle.vert", "Assets/_Engine/Shaders/default_particle.frag")
{
	BorderRadius->Value = 0.3f;
}

void DefaultParticleMaterial::OnRenderSetup() const
{
	IsSpriteValid->Value = Sprite->HasValue();
}
