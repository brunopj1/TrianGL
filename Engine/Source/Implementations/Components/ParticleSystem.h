#pragma once

#include "Implementations/Assets/DefaultParticleMaterial.h"
#include <Game/Component.h>
#include <Game/Rendering/Renderable.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Memory/SharedPtr.h>

// TODO allow resizing the particle system
// TODO remove the transform from the particle system
// TODO add the asserts (is engine initialized, etc)

namespace TGL
{
    struct ParticleSpawnData final
    {
        glm::vec2 Position, Velocity;
        glm::vec4 StartColor, EndColor;
        float StartScale, EndScale;
        float StartRotation, EndRotation;
        bool RotationInDegrees;
        float Duration;
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
        unsigned int m_MaxParticles;
        unsigned int m_NextUnusedParticleIndex = 0;
        
    private:
        SharedPtr<Material> m_Material = nullptr;
        
    private:
        unsigned int m_ParticleVao = 0;
        unsigned int m_ParticleVbo = 0;
        
    public:
        ParticleSystem(unsigned int maxParticles = 1000, SharedPtr<Material> material = nullptr);
        ~ParticleSystem() override = default;

    public:
        SharedPtr<Material> GetMaterial() const;
        void SetMaterial(SharedPtr<Material> material);
        SharedPtr<DefaultParticleMaterial> UseDefaultMaterial();

    public:
        bool Emit(const ParticleSpawnData& spawnData);
        
    private:
        void OnUpdate(float deltaTime) override;

    protected:
        void Render() override;

    private:
        void Init();
        void Terminate();
        
    private:
        unsigned int GetNextUnusedParticleIndex();
    };
}
