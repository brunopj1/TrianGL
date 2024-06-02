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
    void OnUpdate(float deltaTime) override;
    void OnEarlyUpdate(float deltaTime) override;
    void OnLateUpdate(float deltaTime) override;
};
