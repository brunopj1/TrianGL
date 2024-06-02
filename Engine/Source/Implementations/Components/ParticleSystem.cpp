#include "Assets/Material.h"
#include "Assets/Internal/Quad.h"
#include "Util/RandomNumberGenerator.h"

#include <Implementations/Components/ParticleSystem.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

ParticleSystem::ParticleSystem(const unsigned int maxParticles)
    : Component(true), m_MaxParticles(maxParticles)
{
    Init();
}

SharedPtr<Material> ParticleSystem::GetMaterial() const
{
    return m_Material;
}

void ParticleSystem::SetMaterial(SharedPtr<Material> material)
{
    m_Material = std::move(material);
}

bool ParticleSystem::Emit(const glm::vec2& position, const glm::vec2& velocity, const glm::vec4& color, const float life)
{
    const unsigned int nextIndex = GetNextUnusedParticleIndex();
    if (nextIndex == m_MaxParticles) return false;
    
    m_Particles[nextIndex].Position = position;
    m_Particles[nextIndex].Velocity = velocity;
    m_Particles[nextIndex].Color = color;
    m_Particles[nextIndex].Life = life;

    return true;
}

void ParticleSystem::OnUpdate(const float deltaTime)
{
    for (auto& particle : m_Particles)
    {
        if (particle.Life <= 0.0f) continue;

        particle.Position += particle.Velocity * deltaTime;
        particle.Life -= deltaTime;
    }

    UpdateParticleBuffer();
}

void ParticleSystem::Render()
{
    if (m_Material == nullptr) return;

    const glm::mat4 parentModelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 rendererModelMatrix = GetTransform().GetTransformMatrix();

    glm::mat4 modelMatrix = parentModelMatrix * rendererModelMatrix;

    if (const int zIndex = GetZIndex(); zIndex != 0)
    {
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<float>(zIndex)));
    }

    m_Material->Use(modelMatrix);

    glBindVertexArray(m_ParticleVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::s_QuadEbo);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_MaxParticles);

    glBindVertexArray(0);
}

void ParticleSystem::Init()
{
    m_Particles.resize(m_MaxParticles);
    
    glGenVertexArrays(1, &m_ParticleVao);
    glBindVertexArray(m_ParticleVao);

    // Bind the quad EBO and VBO and setup the attributes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::s_QuadEbo);
    glBindBuffer(GL_ARRAY_BUFFER, Quad::s_QuadVbo);
    Quad::BindAttributes();
    
    glGenBuffers(1, &m_ParticleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVbo);
    UpdateParticleBuffer(false);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, Position));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, Velocity));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, Color));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, Life));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);
}

void ParticleSystem::Terminate()
{
    glDeleteBuffers(1, &m_ParticleVbo);
    m_ParticleVbo = 0;

    glDeleteVertexArrays(1, &m_ParticleVao);
    m_ParticleVao = 0;
}

void ParticleSystem::UpdateParticleBuffer(const bool bindBuffer) const
{
    if (bindBuffer) glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVbo);
    
    glBufferData(GL_ARRAY_BUFFER, m_MaxParticles * sizeof(Particle), m_Particles.data(), GL_STREAM_DRAW);
}

// TODO optimize this
unsigned int ParticleSystem::GetNextUnusedParticleIndex() const
{
    for (unsigned int i = 0; i < m_MaxParticles; ++i)
    {
        if (m_Particles[i].Life <= 0.0f)
        {
            return i;
        }
    }

    return m_MaxParticles;
}
