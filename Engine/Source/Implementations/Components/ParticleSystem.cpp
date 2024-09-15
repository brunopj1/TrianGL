#include "Assets/Material.h"
#include "Core/Services/Backends/RenderBackend.h"
#include <Implementations/Components/ParticleSystem.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

ParticleSystem::ParticleSystem(const u32 maxParticles, SharedPtr<Material> material)
	: Component(true), m_MaxParticles(maxParticles), m_Material(std::move(material))
{
	Init();
}

ParticleSystem::~ParticleSystem()
{
	Terminate();
}
u32 ParticleSystem::GetMaxParticles() const
{
	return m_MaxParticles;
}

u32 ParticleSystem::GetParticleCount() const
{
	u32 count = 0;

	for (u32 i = 0; i <= m_LastUsedParticleIndex; i++)
	{
		if (m_ParticlesCpu[i].RemainingDuration > 0.0f)
		{
			count++;
		}
	}

	return count;
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
	const u32 nextIndex = GetNextUnusedParticleIndex();
	if (nextIndex == m_MaxParticles)
	{
		return false;
	}

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

void ParticleSystem::OnUpdate(const f32 deltaTime)
{
	for (u32 i = 0; i <= m_LastUsedParticleIndex; i++)
	{
		auto& cpuParticle = m_ParticlesCpu[i];
		auto& gpuParticle = m_ParticlesGpu[i];

		if (cpuParticle.RemainingDuration <= 0.0f)
		{
			continue;
		}

		const f32 interp = 1.0f - cpuParticle.RemainingDuration / cpuParticle.TotalDuration;

		gpuParticle.Position += cpuParticle.Velocity * deltaTime;

		gpuParticle.Color = glm::mix(cpuParticle.StartColor, cpuParticle.EndColor, interp); // NOLINT(CppRedundantQualifier)
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

	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.UpdateBufferData(m_ParticleVbo, BufferType::ArrayBuffer, 0, m_MaxParticles * sizeof(ParticleGpuData), m_ParticlesGpu.data());

	while (m_ParticlesCpu[m_LastUsedParticleIndex].RemainingDuration <= 0.0f && m_LastUsedParticleIndex > 0)
	{
		m_LastUsedParticleIndex--;
	}
}

void ParticleSystem::Render() const
{
	if (m_Material == nullptr)
	{
		return;
	}

	glm::mat4 modelMatrix = GetParent()->GetTransform().GetTransformMatrix();

	if (const i32 zIndex = GetZIndex(); zIndex != 0)
	{
		modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<f32>(zIndex)));
	}

	m_Material->Use(modelMatrix);

	RenderBackend& renderBackend = RenderBackend::Get();
	const AssetManager& assetManager = AssetManager::Get();
	renderBackend.DrawElementsInstanced(m_ParticleVao, assetManager.GetQuadEbo(), 6, m_LastUsedParticleIndex + 1);
}

void ParticleSystem::Init()
{
	RenderBackend& renderBackend = RenderBackend::Get();

	m_ParticlesCpu.resize(m_MaxParticles);
	m_ParticlesGpu.resize(m_MaxParticles);

	renderBackend.GenerateVertexArray(m_ParticleVao);

	const AssetManager& assetManager = AssetManager::Get();

	// Bind the quad EBO and VBO and setup the attributes
	renderBackend.BindBuffer(assetManager.GetQuadEbo(), BufferType::ElementArrayBuffer);
	renderBackend.BindBuffer(assetManager.GetQuadVbo(), BufferType::ArrayBuffer);
	assetManager.SetupQuadVertexAttributes();

	renderBackend.GenerateBuffer(m_ParticleVbo, BufferType::ArrayBuffer);
	renderBackend.SetBufferData(m_ParticleVbo, BufferType::ArrayBuffer, BufferDrawType::StreamDraw, m_MaxParticles * sizeof(ParticleGpuData), nullptr);

	renderBackend.SetVertexAttributePointerForInstancing(2, 2, VertexAttributeDataType::F32, false, sizeof(ParticleGpuData), offsetof(ParticleGpuData, Position));
	renderBackend.SetVertexAttributePointerForInstancing(3, 4, VertexAttributeDataType::F32, false, sizeof(ParticleGpuData), offsetof(ParticleGpuData, Color));
	renderBackend.SetVertexAttributePointerForInstancing(4, 1, VertexAttributeDataType::F32, false, sizeof(ParticleGpuData), offsetof(ParticleGpuData, Scale));
	renderBackend.SetVertexAttributePointerForInstancing(5, 1, VertexAttributeDataType::F32, false, sizeof(ParticleGpuData), offsetof(ParticleGpuData, Rotation));
	renderBackend.SetVertexAttributePointerForInstancing(6, 1, VertexAttributeDataType::F32, false, sizeof(ParticleGpuData), offsetof(ParticleGpuData, RemainingDuration));

	renderBackend.UnbindVertexArray();
}

void ParticleSystem::Terminate()
{
	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.DeleteBuffer(m_ParticleVbo);
	m_ParticleVbo = 0;

	renderBackend.DeleteVertexArray(m_ParticleVao);
	m_ParticleVao = 0;
}

u32 ParticleSystem::GetNextUnusedParticleIndex()
{
	const u32 nextIndex = m_NextUnusedParticleIndex;
	m_NextUnusedParticleIndex = m_MaxParticles;

	for (u32 i = nextIndex + 1; i < m_MaxParticles; ++i)
	{
		if (m_ParticlesCpu[i].RemainingDuration <= 0.0f)
		{
			m_NextUnusedParticleIndex = i;
			break;
		}
	}

	if (nextIndex > m_LastUsedParticleIndex && nextIndex < m_MaxParticles)
	{
		m_LastUsedParticleIndex = nextIndex;
	}

	return nextIndex;
}
