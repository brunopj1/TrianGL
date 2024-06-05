#include "MouseParticleEmitter.h"

#include "Assets/Material.h"
#include "Core/InputSystem.h"
#include "glm/ext/scalar_constants.hpp"
#include "Implementations/Entities/Camera.h"
#include <imgui.h>

using namespace TGL;

MouseParticleEmitter::MouseParticleEmitter()
    : Entity(true)
{
    m_ParticleSystem = AttachComponent<ParticleSystem>(3000);
    m_Material = m_ParticleSystem->UseDefaultMaterial();

    TextureParameters params;
    params.Filter = TextureFilterMode::Nearest;
    params.MipmapFilter = TextureFilterMode::Nearest;
    
    m_Texture = Texture::Load("Assets/Textures/spritesheet.png", params);
    m_Texture->CreateSliceGrid({15, 15});
}

void MouseParticleEmitter::OnUpdate(const float deltaTime)
{
    RenderImGui();
    
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
        ParticleSpawnData spawnData;

        spawnData.Position = mouseWorldPosition;
        
        spawnData.Duration = m_Random.GetFloat(m_MinDuration, m_MaxDuration);

        const float angle = m_Random.GetFloat(0.0f, 2.0f * glm::pi<float>());
        spawnData.Velocity = glm::vec2(cos(angle), sin(angle)) * m_Random.GetFloat(m_MinVelocity, m_MaxVelocity);
        
        spawnData.StartScale = m_Random.GetFloat(m_MinStartScale, m_MaxStartScale);
        spawnData.EndScale = spawnData.StartScale * m_Random.GetFloat(m_MinScaleFactor, m_MaxScaleFactor);

        spawnData.RotationInDegrees = true;
        spawnData.StartRotation = m_Random.GetFloat(m_MinStartRotation, m_MaxStartRotation);
        spawnData.EndRotation = spawnData.StartRotation + m_Random.GetFloat(m_MinRotationVariation, m_MaxRotationVariation);

        spawnData.StartColor = glm::vec4(mix(m_StartColor1, m_StartColor2, m_Random.GetFloat(0.0f, 1.0f)), 1.0f);
        spawnData.EndColor = glm::vec4(mix(m_EndColor1, m_EndColor2, m_Random.GetFloat(0.0f, 1.0f)), 1.0f);
        
        m_ParticleSystem->Emit(spawnData);
    }

    m_Timer = 1.0f / m_TicksPerSecond;
}

void MouseParticleEmitter::RenderImGui()
{
    ImGui::SetNextWindowPos({30, 30}, ImGuiCond_Appearing);
    ImGui::SetNextWindowSize({300, 300}, ImGuiCond_Appearing);
    
    if (ImGui::Begin("Mouse Particle Settings"))
    {
        RenderImGuiRangeFloat("Duration", m_MinDuration, m_MaxDuration, 0.1f, 10.0f);

        RenderImGuiRangeFloat("Velocity", m_MinVelocity, m_MaxVelocity, 0.1f, 2.0f);

        RenderImGuiRangeFloat("Start Scale", m_MinStartScale, m_MaxStartScale, 0.1f, 2.0f);

        RenderImGuiRangeFloat("Scale Factor", m_MinScaleFactor, m_MaxScaleFactor, 0.0f, 2.0f);

        RenderImGuiRangeFloat("Start Rotation", m_MinStartRotation, m_MaxStartRotation, -180.0f, 180.0f);

        RenderImGuiRangeFloat("Rotation Variation", m_MinRotationVariation, m_MaxRotationVariation, -360.0f, 360.0f);

        RenderImGuiRangeColor("Start Color", m_StartColor1, m_StartColor2);

        RenderImGuiRangeColor("End Color", m_EndColor1, m_EndColor2);

        RenderImGuiMaterialSettings();
    }

    ImGui::End();
}

void MouseParticleEmitter::RenderImGuiRangeFloat(const char* label, float& value1, float& value2, const float min, const float max)
{
    ImGui::Text("%s", label);

    ImGui::PushID(label);

    if (ImGui::SliderFloat("Min", &value1, min, max) && value1 > value2)
    {
        value2 = value1;
    }
    
    if (ImGui::SliderFloat("Max", &value2, min, max) && value2 < value1)
    {
        value1 = value2;
    }

    ImGui::PopID();
    
    ImGui::Separator();
}

void MouseParticleEmitter::RenderImGuiRangeColor(const char* label, glm::vec3& value1, glm::vec3& value2)
{
    ImGui::Text("%s", label);

    ImGui::PushID(label);

    ImGui::ColorEdit3("Color 1", &value1.x);

    ImGui::ColorEdit3("Color 2", &value2.x);

    ImGui::PopID();

    ImGui::Separator();
}

void MouseParticleEmitter::RenderImGuiMaterialSettings()
{
    ImGui::Text("Border Radius");

    ImGui::PushID("Border Radius");

    float& value = m_Material->BorderRadius->Value;

    ImGui::SliderFloat("Value", &value, 0.0f, 0.5f);

    ImGui::PopID();

    ImGui::Separator();

    // -----------------------------------------------

    ImGui::Text("Sprite");

    ImGui::PushID("Sprite");

    if (ImGui::RadioButton("None", &m_SelectedTexture, 0))
    {
        m_Material->Sprite->Value = nullptr;
    }

    ImGui::SameLine();
    
    if (ImGui::RadioButton("Heart", &m_SelectedTexture, 1))
    {
        m_Material->Sprite->Value = m_Texture->GetSlice(0);
    }

    ImGui::SameLine();
    
    if (ImGui::RadioButton("Donut", &m_SelectedTexture, 2))
    {
        m_Material->Sprite->Value = m_Texture->GetSlice(1);
    }

    ImGui::PopID();
}
