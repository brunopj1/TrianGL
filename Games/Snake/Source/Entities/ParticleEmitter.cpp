#include "ParticleEmitter.h"

#include "GameMode/RenderingOrder.h"
#include "glm/ext/scalar_constants.hpp"

ParticleEmitter::ParticleEmitter()
	: Entity(false)
{
	m_ParticleSystem = AttachComponent<TGL::DefaultParticleSystem>(1000);
	m_ParticleSystem->SetZIndex(static_cast<i32>(RenderingOrder::Particles));

	const auto material = m_ParticleSystem->UseDefaultMaterial();
	material->FadeDuration->Value = 0.5f;
	material->BorderRadius->Value = 0.0f;
}

void ParticleEmitter::Emit(const glm::ivec2& cellPosition, ParticleType type)
{
	constexpr i32 count = 30;

	constexpr f32 angleStep = 2 * glm::pi<f32>() / count;
	constexpr f32 angleVariation = angleStep * 0.5f;

	constexpr f32 minSpeed = 0.5f;
	constexpr f32 maxSpeed = 2.0f;

	constexpr f32 minScale = 0.08f;
	constexpr f32 maxScale = 0.12f;

	constexpr f32 minScaleVariation = 0.02f;
	constexpr f32 maxScaleVariation = 0.08f;

	constexpr f32 minRotationVariation = 20.0f;
	constexpr f32 maxRotationVariation = 40.0f;

	constexpr glm::vec4 damageColor1 = {0.91f, 0.16f, 0.00f, 1.0f};
	constexpr glm::vec4 damageColor2 = {0.55f, 0.13f, 0.04f, 1.0f};

	constexpr glm::vec4 growColor1 = {0.91f, 0.78f, 0.00f, 1.0f};
	constexpr glm::vec4 growColor2 = {0.88f, 0.62f, 0.11f, 1.0f};

	constexpr f32 baseDuration = 0.6f;
	constexpr f32 deltaDuration = 0.3f;

	for (i32 i = 0; i < count; i++)
	{
		TGL::ParticleSpawnData spawnData;

		const f32 angle = angleStep * i + m_Random.GetFloat(-angleVariation, angleVariation);
		const glm::vec2 direction = glm::vec2(std::cos(angle), std::sin(angle));
		const f32 speed = m_Random.GetFloat(minSpeed, maxSpeed);

		spawnData.Position = glm::vec2(cellPosition) + 0.5f + direction * 0.25f;
		spawnData.Velocity = direction * speed;

		float rotationVariation = m_Random.GetFloat(minRotationVariation, maxRotationVariation);
		if (m_Random.GetBool())
		{
			rotationVariation *= -1.0f;
		}
		spawnData.StartRotation = m_Random.GetFloat(0.0f, 360.0f);
		spawnData.EndRotation = spawnData.StartRotation + rotationVariation;

		spawnData.StartScale = m_Random.GetFloat(minScale, maxScale);
		spawnData.EndScale = spawnData.StartScale + m_Random.GetFloat(minScaleVariation, maxScaleVariation);

		if (type == ParticleType::Grow)
		{
			spawnData.StartColor = glm::mix(growColor1, growColor2, m_Random.GetFloat(0.0f, 1.0f));
			spawnData.EndColor = glm::mix(growColor1, growColor2, m_Random.GetFloat(0.0f, 1.0f));
		}
		else /* type == ParticleType::Damage */
		{
			spawnData.StartColor = glm::mix(damageColor1, damageColor2, m_Random.GetFloat(0.0f, 1.0f));
			spawnData.EndColor = glm::mix(damageColor1, damageColor2, m_Random.GetFloat(0.0f, 1.0f));
		}

		spawnData.Duration = baseDuration + m_Random.GetFloat(-deltaDuration * 0.5, deltaDuration * 0.5);

		m_ParticleSystem->Emit(spawnData);
	}
}
