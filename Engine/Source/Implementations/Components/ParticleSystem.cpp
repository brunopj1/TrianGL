#include "Assets/Material.h"
#include "Assets/Internal/Quad.h"

#include <Implementations/Components/ParticleSystem.h>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

ParticleSystem::ParticleSystem(const unsigned int maxParticles, SharedPtr<Material> material)
    : Component(true), m_MaxParticles(maxParticles), m_Material(std::move(material))
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

SharedPtr<DefaultParticleMaterial> ParticleSystem::UseDefaultMaterial()
{
    auto defaultMaterial = Material::CreateInstanceOf<DefaultParticleMaterial>();
    m_Material = defaultMaterial;
    return defaultMaterial;
}

bool ParticleSystem::Emit(const ParticleSpawnData& spawnData)
{
    const unsigned int nextIndex = GetNextUnusedParticleIndex();
    if (nextIndex == m_MaxParticles) return false;

    auto& cpuParticle = m_ParticlesCpu[nextIndex];
    auto& gpuParticle = m_ParticlesGpu[nextIndex];

    gpuParticle.Position = spawnData.Position;
    cpuParticle.Velocity = spawnData.Velocity;
    
    cpuParticle.StartColor = spawnData.StartColor;
    cpuParticle.EndColor = spawnData.EndColor;

    cpuParticle.StartScale = spawnData.StartScale;
    cpuParticle.EndScale = spawnData.EndScale;

    if (spawnData.RotationInDegrees)
    {
        cpuParticle.StartRotation = glm::radians(spawnData.StartRotation);
        cpuParticle.EndRotation = glm::radians(spawnData.EndRotation);
    }
    else
    {
        cpuParticle.StartRotation = spawnData.StartRotation;
        cpuParticle.EndRotation = spawnData.EndRotation;
    }

    cpuParticle.TotalDuration = spawnData.Duration;
    cpuParticle.RemainingDuration = spawnData.Duration;
    gpuParticle.RemainingDuration = spawnData.Duration;
    
    return true;
}

void ParticleSystem::OnUpdate(const float deltaTime)
{
    for (int i = 0; i < m_MaxParticles; i++)
    {
        auto& cpuParticle = m_ParticlesCpu[i];
        auto& gpuParticle = m_ParticlesGpu[i];
        
        if (cpuParticle.RemainingDuration <= 0.0f) continue;

        const float interp = 1.0f - (cpuParticle.RemainingDuration / cpuParticle.TotalDuration);

        gpuParticle.Position += cpuParticle.Velocity * deltaTime;

        gpuParticle.Color = glm::mix(cpuParticle.StartColor, cpuParticle.EndColor, interp);
        gpuParticle.Scale = glm::mix(cpuParticle.StartScale, cpuParticle.EndScale, interp);
        gpuParticle.Rotation = glm::mix(cpuParticle.StartRotation, cpuParticle.EndRotation, interp);

        cpuParticle.RemainingDuration -= deltaTime;
        gpuParticle.RemainingDuration = cpuParticle.RemainingDuration;

        if (cpuParticle.RemainingDuration <= 0.0f)
        {
            if (i < m_NextUnusedParticleIndex)
            {
                m_NextUnusedParticleIndex = i;
            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_MaxParticles * sizeof(ParticleGpuData), m_ParticlesGpu.data());
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
    m_ParticlesCpu.resize(m_MaxParticles);
    m_ParticlesGpu.resize(m_MaxParticles);
    
    glGenVertexArrays(1, &m_ParticleVao);
    glBindVertexArray(m_ParticleVao);

    // Bind the quad EBO and VBO and setup the attributes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::s_QuadEbo);
    glBindBuffer(GL_ARRAY_BUFFER, Quad::s_QuadVbo);
    Quad::BindAttributes();
    
    glGenBuffers(1, &m_ParticleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVbo);
    glBufferData(GL_ARRAY_BUFFER, m_MaxParticles * sizeof(ParticleGpuData), nullptr, GL_STREAM_DRAW);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleGpuData), (void*)offsetof(ParticleGpuData, Position));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleGpuData), (void*)offsetof(ParticleGpuData, Color));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpuData), (void*)offsetof(ParticleGpuData, Scale));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpuData), (void*)offsetof(ParticleGpuData, Rotation));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);
    
    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr, performance-no-int-to-ptr
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleGpuData), (void*)offsetof(ParticleGpuData, RemainingDuration));
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}

void ParticleSystem::Terminate()
{
    glDeleteBuffers(1, &m_ParticleVbo);
    m_ParticleVbo = 0;

    glDeleteVertexArrays(1, &m_ParticleVao);
    m_ParticleVao = 0;
}

unsigned int ParticleSystem::GetNextUnusedParticleIndex()
{
    const unsigned int nextIndex = m_NextUnusedParticleIndex;
    m_NextUnusedParticleIndex = m_MaxParticles;
    
    for (unsigned int i = nextIndex; i < m_MaxParticles; ++i)
    {
        if (m_ParticlesCpu[i].RemainingDuration <= 0.0f)
        {
            m_NextUnusedParticleIndex = i;
            break;
        }
    }

    return nextIndex;
}
