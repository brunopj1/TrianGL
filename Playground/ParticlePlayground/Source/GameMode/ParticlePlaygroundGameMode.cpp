#include "ParticlePlaygroundGameMode.h"

#include "Core/Services/Public/InputSystem.h"
#include "General/Camera.h"

using namespace TGL;

ParticlePlaygroundGameMode::ParticlePlaygroundGameMode()
{
	Camera* camera = SpawnEntity<Camera>(true);

	m_ParticleEmitter = SpawnEntity<MouseParticleEmitter>();
}

void ParticlePlaygroundGameMode::OnUpdate(f32 deltaTime) {}

void ParticlePlaygroundGameMode::OnEarlyUpdate(f32 deltaTime) {}

void ParticlePlaygroundGameMode::OnLateUpdate(f32 deltaTime) {}
