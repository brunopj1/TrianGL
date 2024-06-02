#pragma once

#include <Game/Component.h>
#include <Game/Rendering/Renderable.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <Memory/SharedPtr.h>

// TODO add the asserts (is engine initialized, etc)

namespace TGL
{
    struct Particle final // TODO make this internal ?
    {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec4 Color;
        float Life;
    };
    
    class ParticleSystem final : public Component, public Renderable
    {
    private:
        std::vector<Particle> m_Particles;
        unsigned int m_MaxParticles;
        
    private:
        SharedPtr<Material> m_Material = nullptr;
        
    private:
        unsigned int m_ParticleVao = 0;
        unsigned int m_ParticleVbo = 0;
        
    public:
        ParticleSystem(unsigned int maxParticles = 1000);
        ~ParticleSystem() override = default;

    public:
        SharedPtr<Material> GetMaterial() const;
        void SetMaterial(SharedPtr<Material> material);
        // TODO default material?

    public:
        bool Emit(const glm::vec2& position, const glm::vec2& velocity, const glm::vec4& color, float life);
        
    private:
        void OnUpdate(float deltaTime) override;

    protected:
        void Render() override;

    private:
        void Init();
        void Terminate();

    private:
        void UpdateParticleBuffer(bool bindBuffer = true) const;

    private:
        unsigned int GetNextUnusedParticleIndex() const;
    };
}
