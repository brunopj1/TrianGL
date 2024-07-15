#pragma once

#include "Implementations/Components/ParticleSystem.h"
#include "Util/RandomNumberGenerator.h"

enum class ParticleType
{
    Grow,
    Damage
};

class ParticleEmitter final : public TGL::Entity
{
public:
    TGL::ParticleSystem* m_ParticleSystem;
    TGL::RandomNumberGenerator m_Random;

public:
    ParticleEmitter();
    ~ParticleEmitter() override = default;

public:
    void Emit(const glm::ivec2& cellPosition, ParticleType type);
};
