#pragma once

#include "Core/Internal/Concepts/ParticleSystemConcepts.h"
#include "Implementations/Materials/DefaultParticleMaterial.h"
#include <Core/Services/Backends/RenderBackend.h>
#include <Game/Component.h>
#include <Game/Internal/Renderable.h>
#include <Memory/SharedPtr.h>
#include <glm/gtc/matrix_transform.hpp>

namespace TGL
{
	enum class ParticleDataType : u16
	{
		I8 = 0x1400, // GL_BYTE
		U8 = 0x1401, // GL_UNSIGNED_BYTE
		I16 = 0x1402, // GL_SHORT
		U16 = 0x1403, // GL_UNSIGNED_SHORT
		I32 = 0x1404, // GL_INT
		U32 = 0x1405, // GL_UNSIGNED_INT
		F32 = 0x1406, // GL_FLOAT
		F64 = 0x140A // GL_DOUBLE
	};

	struct ParticleDataInfo final
	{
		ParticleDataType DataType;
		u8 Size;
		bool Normalized;
	};

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	class ParticleSystem : public Component, public Renderable // NOLINT(CppClassCanBeFinal)
	{
	private:
		std::vector<CpuParticle> m_CpuParticles;
		std::vector<GpuParticle> m_GpuParticles;
		u32 m_MaxParticles;

		u32 m_NextUnusedIndex = 0;
		u32 m_LastUsedIndex = 0;

	private:
		SharedPtr<Material> m_Material = nullptr;

	private:
		u32 m_ParticleVao = 0;
		u32 m_ParticleVbo = 0;

	public:
		ParticleSystem(u32 maxParticles = 1000, SharedPtr<Material> material = nullptr);
		~ParticleSystem() override;

	public:
		u32 GetMaxParticles() const;
		u32 GetParticleCount() const;

	public:
		SharedPtr<Material> GetMaterial() const;
		void SetMaterial(SharedPtr<Material> material);

	public:
		bool Emit(const ParticleSpawnData& spawnData);

	protected:
		virtual void SetupParticle(const ParticleSpawnData& spawnData, CpuParticle& cpuParticle, GpuParticle& gpuParticle) = 0;
		virtual void UpdateParticle(CpuParticle& cpuParticle, GpuParticle& gpuParticle, f32 deltaTime) = 0;
		virtual bool IsParticleAlive(const CpuParticle& cpuParticle, const GpuParticle& gpuParticle) const = 0;

	private:
		void OnUpdate(f32 deltaTime) override;

	private:
		void Render() override;

	private:
		void Init();

		void Terminate();

	private:
		bool UpdateIndices();
	};

	// Template definitions

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::ParticleSystem(const u32 maxParticles, SharedPtr<Material> material)
		: Component(true, I32_MIN), m_MaxParticles(maxParticles), m_Material(std::move(material))
	{
		Init();
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::~ParticleSystem()
	{
		Terminate();
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	u32 ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::GetMaxParticles() const
	{
		return m_MaxParticles;
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	u32 ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::GetParticleCount() const
	{
		u32 count = 0;

		for (u32 i = 0; i <= m_LastUsedIndex; i++)
		{
			const CpuParticle& cpuParticle = m_CpuParticles[i];
			const GpuParticle& gpuParticle = m_GpuParticles[i];

			if (IsParticleAlive(cpuParticle, gpuParticle))
			{
				count++;
			}
		}

		return count;
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	SharedPtr<Material> ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::GetMaterial() const
	{
		return m_Material;
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::SetMaterial(SharedPtr<Material> material)
	{
		m_Material = std::move(material);
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	bool ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::Emit(const ParticleSpawnData& spawnData)
	{
		const u32 nextIndex = m_NextUnusedIndex;
		if (nextIndex == m_MaxParticles)
		{
			return false;
		}

		auto& cpuParticle = m_CpuParticles[nextIndex];
		auto& gpuParticle = m_GpuParticles[nextIndex];

		SetupParticle(spawnData, cpuParticle, gpuParticle);
		const bool isNewParticleAlive = IsParticleAlive(cpuParticle, gpuParticle);

		if (isNewParticleAlive)
		{
			UpdateIndices();
		}

		return isNewParticleAlive;
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::OnUpdate(const f32 deltaTime)
	{
		for (u32 i = 0; i <= m_LastUsedIndex; i++)
		{
			auto& cpuParticle = m_CpuParticles[i];
			auto& gpuParticle = m_GpuParticles[i];

			if (!IsParticleAlive(cpuParticle, gpuParticle))
			{
				continue;
			}

			UpdateParticle(cpuParticle, gpuParticle, deltaTime);

			if (!IsParticleAlive(cpuParticle, gpuParticle))
			{
				if (i < m_NextUnusedIndex)
				{
					m_NextUnusedIndex = i;
				}
			}
		}

		RenderBackend& renderBackend = RenderBackend::Get();
		renderBackend.UpdateBufferData(m_ParticleVbo, BufferType::ArrayBuffer, 0, m_MaxParticles * sizeof(GpuParticle), m_GpuParticles.data());

		while (m_LastUsedIndex > 0)
		{
			CpuParticle& cpuParticle = m_CpuParticles[m_LastUsedIndex];
			GpuParticle& gpuParticle = m_GpuParticles[m_LastUsedIndex];

			if (IsParticleAlive(cpuParticle, gpuParticle))
			{
				break;
			}

			m_LastUsedIndex--;
		}
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::Render()
	{
		if (m_Material == nullptr)
		{
			return;
		}

		const glm::mat4 parentModelMatrix = GetParent()->GetTransform().GetTransformMatrix();
		const glm::mat4 rendererModelMatrix = GetTransform().GetTransformMatrix();

		glm::mat4 modelMatrix = parentModelMatrix * rendererModelMatrix;

		if (const i32 zIndex = GetZIndex(); zIndex != 0)
		{
			modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<f32>(zIndex)));
		}

		m_Material->Use(modelMatrix);

		RenderBackend& renderBackend = RenderBackend::Get();
		const AssetManager& assetManager = AssetManager::Get();
		renderBackend.DrawElementsInstanced(m_ParticleVao, assetManager.GetQuadEbo(), 6, m_LastUsedIndex + 1);
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::Init()
	{
		RenderBackend& renderBackend = RenderBackend::Get();

		m_CpuParticles.resize(m_MaxParticles);
		m_GpuParticles.resize(m_MaxParticles);

		renderBackend.GenerateVertexArray(m_ParticleVao);

		const AssetManager& assetManager = AssetManager::Get();

		// Bind the quad EBO and VBO and setup the attributes
		renderBackend.BindBuffer(assetManager.GetQuadEbo(), BufferType::ElementArrayBuffer);
		renderBackend.BindBuffer(assetManager.GetQuadVbo(), BufferType::ArrayBuffer);
		assetManager.SetupQuadVertexAttributes();

		renderBackend.GenerateBuffer(m_ParticleVbo, BufferType::ArrayBuffer);
		renderBackend.SetBufferData(m_ParticleVbo, BufferType::ArrayBuffer, BufferDrawType::StreamDraw, m_MaxParticles * sizeof(GpuParticle), nullptr);

		const auto particleStructure = GpuParticle::GetParticleStructure();
		u32 index = 2;
		u32 offset = 0;

		for (const auto& particleData : particleStructure)
		{
			const auto dataType = static_cast<VertexAttributeDataType>(particleData.DataType);
			const u8 byteSize = renderBackend.GetDataTypeSize(dataType);

			renderBackend.SetVertexAttributePointerForInstancing(index, particleData.Size, dataType, particleData.Normalized, sizeof(GpuParticle), offset);

			index++;
			offset += particleData.Size * byteSize;
		}

		renderBackend.UnbindVertexArray();
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::Terminate()
	{
		RenderBackend& renderBackend = RenderBackend::Get();

		renderBackend.DeleteBuffer(m_ParticleVbo);
		m_ParticleVbo = 0;

		renderBackend.DeleteVertexArray(m_ParticleVao);
		m_ParticleVao = 0;
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	bool ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::UpdateIndices()
	{
		// Update the next unused index

		const u32 newParticleIndex = m_NextUnusedIndex;
		m_NextUnusedIndex = m_MaxParticles;

		for (u32 i = newParticleIndex + 1; i < m_MaxParticles; ++i)
		{
			CpuParticle& cpuParticle = m_CpuParticles[i];
			GpuParticle& gpuParticle = m_GpuParticles[i];

			if (!IsParticleAlive(cpuParticle, gpuParticle))
			{
				m_NextUnusedIndex = i;
				break;
			}
		}

		// Update the last used index

		if (newParticleIndex > m_LastUsedIndex && newParticleIndex < m_MaxParticles)
		{
			m_LastUsedIndex = newParticleIndex;
		}

		return true;
	}
}
