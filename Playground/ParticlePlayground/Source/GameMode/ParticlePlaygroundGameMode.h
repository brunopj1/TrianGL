#pragma once

#include "Entities/MouseParticleEmitter.h"
#include "Game/GameMode.h"
#include "Implementations/Entities/Camera.h"

class ParticlePlaygroundGameMode : public TGL::GameMode
{
private:
    MouseParticleEmitter* m_ParticleEmitter;
    
public:
    ParticlePlaygroundGameMode();
    ~ParticlePlaygroundGameMode() override = default;

private:
    void OnUpdate(f32 deltaTime) override;
    void OnEarlyUpdate(f32 deltaTime) override;
    void OnLateUpdate(f32 deltaTime) override;
};
