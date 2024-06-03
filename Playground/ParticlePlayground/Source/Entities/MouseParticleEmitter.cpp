#include "MouseParticleEmitter.h"

#include "Assets/Material.h"
#include "Core/InputSystem.h"
#include "glm/ext/scalar_constants.hpp"
#include "Implementations/Entities/Camera.h"

using namespace TGL;

MouseParticleEmitter::MouseParticleEmitter()
    : Entity(true)
{
    m_ParticleSystem = AttachComponent<ParticleSystem>(3000);
    auto material = m_ParticleSystem->UseDefaultMaterial();
}

void MouseParticleEmitter::OnUpdate(const float deltaTime)
{
    if (m_Timer > 0.0f)
    {
        m_Timer -= deltaTime;
        return;
    }
    
    if (!InputSystem::IsMouseButtonDown(MouseButton::Left)) return;

    const Camera* camera = Camera::GetMainCamera();

    const glm::ivec2 mouseScreenPosition = InputSystem::GetMousePosition();
    const glm::vec2 mouseWorldPosition = camera->ScreenToWorldPosition(mouseScreenPosition);

    // TODO ue ImGui to control the constexpr values
    
    for (int i = 0; i < 3; i++)
    {
        ParticleSpawnData spawnData;

        spawnData.Position = mouseWorldPosition;
        
        constexpr float minVelocity = 0.2f;
        constexpr float maxVelocity = 0.8f;
        const float angle = m_Random.GetFloat(0.0f, 2.0f * glm::pi<float>());
        spawnData.Velocity = glm::vec2(cos(angle), sin(angle)) * m_Random.GetFloat(minVelocity, maxVelocity);
        
        constexpr glm::vec4 startColor1 = glm::vec4(230 / 255.0f, 139 / 255.0f, 41 / 255.0f, 1.0f);
        constexpr glm::vec4 startColor2 = glm::vec4(189 / 255.0f, 64 / 255.0f, 45 / 255.0f, 1.0f);
        spawnData.StartColor = mix(startColor1, startColor2, m_Random.GetFloat(0.0f, 1.0f));

        constexpr glm::vec4 endColor1 = glm::vec4(95 / 255.0f, 5 / 255.0f, 230 / 255.0f, 1.0f);
        constexpr glm::vec4 endColor2 = glm::vec4(139 / 255.0f, 41 / 255.0f, 204 / 255.0f, 1.0f);
        spawnData.EndColor = mix(endColor1, endColor2, m_Random.GetFloat(0.0f, 1.0f));
        
        constexpr float minStartScale = 0.1f;
        constexpr float maxStartScale = 0.3f;
        spawnData.StartScale = m_Random.GetFloat(minStartScale, maxStartScale);
        spawnData.EndScale = spawnData.StartScale * 0.5f;

        spawnData.RotationInDegrees = true;
        
        constexpr float minStartRotation = -15.0f;
        constexpr float maxStartRotation = 15.0f;
        spawnData.StartRotation = m_Random.GetFloat(minStartRotation, maxStartRotation);
        
        constexpr float minRotationVariation = 45.0f;
        constexpr float maxRotationVariation = 60.0f;
        spawnData.EndRotation = spawnData.StartRotation + m_Random.GetFloat(minRotationVariation, maxRotationVariation);
        
        constexpr float life = 3.0f;
        spawnData.Duration = life;

        m_ParticleSystem->Emit(spawnData);
    }

    m_Timer = 1.0f / m_TicksPerSecond;
}