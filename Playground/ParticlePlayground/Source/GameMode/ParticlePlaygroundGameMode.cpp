#include "ParticlePlaygroundGameMode.h"

#include "Core/InputSystem.h"
#include "Implementations/Entities/Camera.h"

using namespace TGL;

ParticlePlaygroundGameMode::ParticlePlaygroundGameMode()
{
    Camera* camera = SpawnEntity<Camera>(true);

    m_ParticleEmitter = SpawnEntity<MouseParticleEmitter>();
}

void ParticlePlaygroundGameMode::OnUpdate(float deltaTime)
{
    
}

void ParticlePlaygroundGameMode::OnEarlyUpdate(float deltaTime)
{
    
}

void ParticlePlaygroundGameMode::OnLateUpdate(float deltaTime)
{
    
}