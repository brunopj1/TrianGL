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
    int m_SelectedTexture = 0;
    TGL::RandomNumberGenerator m_Random;

private:
    int m_TicksPerSecond = 144;
    float m_Timer = 0.0f;

private:
    float m_MinDuration = 1.5f;
    float m_MaxDuration = 3.0f;
        
    float m_MinVelocity = 0.2f;
    float m_MaxVelocity = 0.8f;

    float m_MinStartScale = 0.1f;
    float m_MaxStartScale = 0.3f;

    float m_MinScaleFactor = 0.4f;
    float m_MaxScaleFactor = 0.6f;

    float m_MinStartRotation = -15.0f;
    float m_MaxStartRotation = 15.0f;

    float m_MinRotationVariation = 45.0f;
    float m_MaxRotationVariation = 60.0f;

    glm::vec3 m_StartColor1 = glm::vec4(230 / 255.0f, 139 / 255.0f, 41 / 255.0f, 1.0f);
    glm::vec3 m_StartColor2 = glm::vec4(189 / 255.0f, 64 / 255.0f, 45 / 255.0f, 1.0f);

    glm::vec3 m_EndColor1 = glm::vec4(95 / 255.0f, 5 / 255.0f, 230 / 255.0f, 1.0f);
    glm::vec3 m_EndColor2 = glm::vec4(139 / 255.0f, 41 / 255.0f, 204 / 255.0f, 1.0f);

public:
    MouseParticleEmitter();

protected:
    void OnUpdate(float deltaTime) override;

private:
    void RenderImGui();
    static void RenderImGuiRangeFloat(const char* label, float& value1, float& value2, float min, float max);
    static void RenderImGuiRangeColor(const char* label, glm::vec3& value1, glm::vec3& value2);
    void RenderImGuiMaterialSettings();
};
