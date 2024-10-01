#pragma once

#include "Implementations/Assets/DefaultParticleMaterial.h"
#include <Game/Component.h>
#include <Game/Internal/Renderable.h>
#include <Memory/SharedPtr.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace TGL
{
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

	struct ParticleCpuData final
	{
		glm::vec2 Velocity;
		glm::vec4 StartColor, EndColor;
		f32 StartScale, EndScale;
		f32 StartRotation, EndRotation;
		f32 TotalDuration, RemainingDuration;
	};

	struct ParticleGpuData final
	{
		glm::vec2 Position;
		glm::vec4 Color;
		f32 Scale;
		f32 Rotation;
		f32 RemainingDuration;
	};

	class ParticleSystem : public Component, public Renderable // NOLINT(CppClassCanBeFinal)
	{
	private:
		std::vector<ParticleCpuData> m_ParticlesCpu;
		std::vector<ParticleGpuData> m_ParticlesGpu;
		u32 m_MaxParticles;
		u32 m_NextUnusedParticleIndex = 0;
		u32 m_LastUsedParticleIndex = 0;

	private:
		SharedPtr<Material> m_Material = nullptr;

	private:
		u32 m_ParticleVao = 0;
		u32 m_ParticleVbo = 0;

	public:
		ParticleSystem(u32 maxParticles = 1000, SharedPtr<Material> material = nullptr);
		~ParticleSystem() override;

	public:
		u32 GetMaxParticles() const;
		u32 GetParticleCount() const;

	public:
		SharedPtr<Material> GetMaterial() const;
		void SetMaterial(SharedPtr<Material> material);
		SharedPtr<DefaultParticleMaterial> UseDefaultMaterial();

	public:
		bool Emit(const ParticleSpawnData& spawnData);

	private:
		void OnUpdate(f32 deltaTime) override;

	private:
		void Render() override;

	private:
		void Init();
		void Terminate();

	private:
		u32 GetNextUnusedParticleIndex();
	};
}
