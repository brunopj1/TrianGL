#include "DefaultParticleSystem.h"

using namespace TGL;

std::vector<ParticleDataInfo> GpuParticleData::GetParticleStructure()
{
	return {
		{ParticleDataType::FVEC2, false}, // Position
		{ParticleDataType::FVEC4, false}, // Color
		{ParticleDataType::FLOAT, false}, // Scale
		{ParticleDataType::FLOAT, false}, // Rotation
		{ParticleDataType::FLOAT, false} // RemainingDuration
	};
}

DefaultParticleSystem::DefaultParticleSystem(const u32 maxParticles, SharedPtr<Material> material)
	: ParticleSystem(maxParticles, std::move(material))
{}

SharedPtr<DefaultParticleMaterial> DefaultParticleSystem::UseDefaultMaterial()
{
	auto defaultMaterial = Material::CreateInstanceOf<DefaultParticleMaterial>();
	SetMaterial(defaultMaterial);
	return defaultMaterial;
}

void DefaultParticleSystem::SetupParticle(const ParticleSpawnData& spawnData, CpuParticleData& cpuParticle, GpuParticleData& gpuParticle)
{
	gpuParticle.Position = spawnData.Position;
	cpuParticle.Velocity = spawnData.Velocity;

	cpuParticle.StartColor = spawnData.StartColor;
	cpuParticle.EndColor = spawnData.EndColor;

	cpuParticle.StartScale = spawnData.StartScale;
	cpuParticle.EndScale = spawnData.EndScale;

	if (spawnData.RotationInDegrees)
	{
		cpuParticle.StartRotation = glm::radians(spawnData.StartRotation);
		cpuParticle.EndRotation = glm::radians(spawnData.EndRotation);
	}
	else
	{
		cpuParticle.StartRotation = spawnData.StartRotation;
		cpuParticle.EndRotation = spawnData.EndRotation;
	}

	cpuParticle.TotalDuration = spawnData.Duration;
	cpuParticle.RemainingDuration = spawnData.Duration;
	gpuParticle.RemainingDuration = spawnData.Duration;
}

void DefaultParticleSystem::UpdateParticle(CpuParticleData& cpuParticle, GpuParticleData& gpuParticle, const f32 deltaTime)
{
	const f32 interp = 1.0f - cpuParticle.RemainingDuration / cpuParticle.TotalDuration;

	gpuParticle.Position += cpuParticle.Velocity * deltaTime;

	gpuParticle.Color = glm::mix(cpuParticle.StartColor, cpuParticle.EndColor, interp); // NOLINT(CppRedundantQualifier)
	gpuParticle.Scale = glm::mix(cpuParticle.StartScale, cpuParticle.EndScale, interp);
	gpuParticle.Rotation = glm::mix(cpuParticle.StartRotation, cpuParticle.EndRotation, interp);

	cpuParticle.RemainingDuration -= deltaTime;
	gpuParticle.RemainingDuration = cpuParticle.RemainingDuration;
}

bool DefaultParticleSystem::IsParticleAlive(const CpuParticleData& cpuParticle, const GpuParticleData& gpuParticle) const
{
	return cpuParticle.RemainingDuration > 0.0f;
}
