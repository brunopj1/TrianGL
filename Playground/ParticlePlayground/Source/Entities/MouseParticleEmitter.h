#pragma once

#include "Game/Entity.h"
#include "Implementations/Components/ParticleSystem.h"
#include "Util/RandomNumberGenerator.h"

class MouseParticleEmitter final : public TGL::Entity
{
private:
	TGL::ParticleSystem* m_ParticleSystem;
	TGL::SharedPtr<TGL::DefaultParticleMaterial> m_Material;
	TGL::SharedPtr<TGL::Texture> m_Texture;
	i32 m_SelectedTexture = 0;
	TGL::RandomNumberGenerator m_Random;

private:
	i32 m_TicksPerSecond = 144;
	f32 m_Timer = 0.0f;

private:
	f32 m_MinDuration = 1.5f;
	f32 m_MaxDuration = 3.0f;

	f32 m_MinVelocity = 0.2f;
	f32 m_MaxVelocity = 0.8f;

	f32 m_MinStartScale = 0.1f;
	f32 m_MaxStartScale = 0.3f;

	f32 m_MinScaleFactor = 0.4f;
	f32 m_MaxScaleFactor = 0.6f;

	f32 m_MinStartRotation = -15.0f;
	f32 m_MaxStartRotation = 15.0f;

	f32 m_MinRotationVariation = 45.0f;
	f32 m_MaxRotationVariation = 60.0f;

	glm::vec3 m_StartColor1 = glm::vec4(230 / 255.0f, 139 / 255.0f, 41 / 255.0f, 1.0f);
	glm::vec3 m_StartColor2 = glm::vec4(189 / 255.0f, 64 / 255.0f, 45 / 255.0f, 1.0f);

	glm::vec3 m_EndColor1 = glm::vec4(95 / 255.0f, 5 / 255.0f, 230 / 255.0f, 1.0f);
	glm::vec3 m_EndColor2 = glm::vec4(139 / 255.0f, 41 / 255.0f, 204 / 255.0f, 1.0f);

public:
	MouseParticleEmitter();

protected:
	void OnUpdate(f32 deltaTime) override;

private:
	void RenderImGui();
	static void RenderImGuiRangeFloat(const char* label, f32& value1, f32& value2, f32 min, f32 max);
	static void RenderImGuiRangeColor(const char* label, glm::vec3& value1, glm::vec3& value2);
	void RenderImGuiMaterialSettings();
};
