#include "MouseParticleEmitter.h"

#include "Assets/Material.h"
#include "Core/InputSystem.h"
#include "Implementations/Entities/Camera.h"
#include "Materials/ParticleMaterial.h"

using namespace TGL;

MouseParticleEmitter::MouseParticleEmitter()
    : Entity(true)
{
    m_ParticleSystem = AttachComponent<ParticleSystem>(3000);
    m_ParticleSystem->SetMaterial(Material::CreateInstanceOf<ParticleMaterial>());
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

    for (int i = 0; i < 3; i++)
    {
        constexpr float maxSpeed = 0.5f;
        const glm::vec2 velocity = glm::vec2(m_Random.GetFloat(-maxSpeed, maxSpeed), m_Random.GetFloat(-maxSpeed, maxSpeed));

        constexpr glm::vec4 color1 = glm::vec4(230 / 255.0f, 139 / 255.0f, 41 / 255.0f, 1.0f);
        constexpr glm::vec4 color2 = glm::vec4(189 / 255.0f, 64 / 255.0f, 45 / 255.0f, 1.0f);
        const glm::vec4 color = glm::mix(color1, color2, m_Random.GetFloat(0.0f, 1.0f));

        constexpr float life = 3.0f;

        m_ParticleSystem->Emit(mouseWorldPosition, velocity, color, life);
    }

    m_Timer = 1.0f / m_TicksPerSecond;
}