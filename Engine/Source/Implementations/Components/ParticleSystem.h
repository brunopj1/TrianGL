#pragma once

#include "Implementations/Assets/DefaultParticleMaterial.h"
#include <Game/Component.h>
#include <Game/Rendering/Renderable.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Memory/SharedPtr.h>

namespace TGL
{
    struct ParticleSpawnData final
    {
        glm::vec2 Position = { 0.0f, 0.0f };
        glm::vec2 Velocity = { 0.0f, 0.0f };
        
        glm::vec4 StartColor = {1.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 EndColor = {0.0f, 0.0f, 0.0f, 0.0f };
        
        float StartScale = 1.0f;
        float EndScale = 1.0f;
        
        float StartRotation = 0.0f;
        float EndRotation = 0.0f;
        
        bool RotationInDegrees = true;
        
        float Duration = 1.0f;
    };

    struct ParticleCpuData final
    {
        glm::vec2 Velocity;
        glm::vec4 StartColor, EndColor;
        float StartScale, EndScale;
        float StartRotation, EndRotation;
        float TotalDuration, RemainingDuration;
    };

    struct ParticleGpuData final
    {
        glm::vec2 Position;
        glm::vec4 Color;
        float Scale;
        float Rotation;
        float RemainingDuration;
    };
    
    class ParticleSystem final : public Component, public Renderable
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
        SharedPtr<Material> GetMaterial() const;
        void SetMaterial(SharedPtr<Material> material);
        SharedPtr<DefaultParticleMaterial> UseDefaultMaterial();

    public:
        bool Emit(const ParticleSpawnData& spawnData);
        
    private:
        void OnUpdate(float deltaTime) override;

    protected:
        void Render() const override;

    private:
        void Init();
        void Terminate();
        
    private:
        u32 GetNextUnusedParticleIndex();
    };
}
