#pragma once

#include "Game/Entity.h"
#include "Implementations/Components/ParticleSystem.h"
#include "Util/RandomNumberGenerator.h"

class MouseParticleEmitter final : public TGL::Entity
{
private:
    TGL::ParticleSystem* m_ParticleSystem;
    TGL::RandomNumberGenerator m_Random;

private:
    int m_TicksPerSecond = 144;
    float m_Timer = 0.0f;
    
public:
    MouseParticleEmitter();

protected:
    void OnUpdate(float deltaTime) override;
};
