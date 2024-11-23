#pragma once

#include "Implementations/ParticleSystems/DefaultParticleSystem.h"
#include "Util/RandomNumberGenerator.h"

enum class ParticleType : u8
{
	Grow,
	Damage
};

class ParticleEmitter final : public TGL::Entity
{
public:
	TGL::DefaultParticleSystem* m_ParticleSystem;
	TGL::RandomNumberGenerator m_Random;

public:
	ParticleEmitter();
	~ParticleEmitter() override = default;

public:
	void Emit(const glm::ivec2& cellPosition, ParticleType type);
};
