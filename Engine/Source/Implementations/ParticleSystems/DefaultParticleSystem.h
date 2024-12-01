#pragma once
#include "Rendering/ParticleSystem.h"

namespace TGL
{
	struct CpuParticleData final
	{
		glm::vec2 Velocity;
		glm::vec4 StartColor, EndColor;
		f32 StartScale, EndScale;
		f32 StartRotation, EndRotation;
		f32 TotalDuration, RemainingDuration;
	};

	struct GpuParticleData final
	{
		glm::vec2 Position;
		glm::vec4 Color;
		f32 Scale;
		f32 Rotation;
		f32 RemainingDuration;

		// TODO when available, use reflection to get this data
		static std::vector<ParticleDataInfo> GetParticleStructure();
	};

	struct ParticleSpawnData final
	{
		glm::vec2 Position = {0.0f, 0.0f};
		glm::vec2 Velocity = {0.0f, 0.0f};

		glm::vec4 StartColor = {1.0f, 1.0f, 1.0f, 1.0f};
		glm::vec4 EndColor = {0.0f, 0.0f, 0.0f, 0.0f};

		f32 StartScale = 1.0f;
		f32 EndScale = 1.0f;

		f32 StartRotation = 0.0f;
		f32 EndRotation = 0.0f;

		bool RotationInDegrees = true;

		f32 Duration = 1.0f;
	};

	class DefaultParticleSystem : public ParticleSystem<CpuParticleData, GpuParticleData, ParticleSpawnData> // NOLINT(CppClassCanBeFinal)
	{
	public:
		DefaultParticleSystem(u32 maxParticles = 1000, SharedPtr<Material> material = nullptr);
		~DefaultParticleSystem() override = default;

	public:
		SharedPtr<DefaultParticleMaterial> UseDefaultMaterial();

	protected:
		void SetupParticle(const ParticleSpawnData& spawnData, CpuParticleData& cpuParticle, GpuParticleData& gpuParticle) override;
		void UpdateParticle(CpuParticleData& cpuParticle, GpuParticleData& gpuParticle, f32 deltaTime) override;
		bool IsParticleAlive(const CpuParticleData& cpuParticle, const GpuParticleData& gpuParticle) const override;
	};

}
