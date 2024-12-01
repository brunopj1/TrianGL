#pragma once

#include "Core/Internal/Concepts/ParticleSystemConcepts.h"
#include "Exceptions/Assets/IncompatibleMaterialException.h"
#include "Implementations/Materials/DefaultParticleMaterial.h"
#include <Core/Services/Backends/RenderBackend.h>
#include <Game/Component.h>
#include <Game/Internal/Renderable.h>
#include <Memory/SharedPtr.h>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

namespace TGL
{
	// NOLINTBEGIN(CppInconsistentNaming)
	// clang-format off

	enum class ParticleDataType : u16
	{
		INT   = 0x1404, // GL_INT
		UINT  = 0x1405, // GL_UNSIGNED_INT
		FLOAT = 0x1406, // GL_FLOAT
		IVEC2 = 0x8B53, // GL_INT_VEC2
		IVEC3 = 0x8B54, // GL_INT_VEC3
		IVEC4 = 0x8B55, // GL_INT_VEC4
		UVEC2 = 0x8DC6, // GL_UNSIGNED_INT_VEC2
		UVEC3 = 0x8DC7, // GL_UNSIGNED_INT_VEC3
		UVEC4 = 0x8DC8, // GL_UNSIGNED_INT_VEC4
		FVEC2 = 0x8B50, // GL_FLOAT_VEC2
		FVEC3 = 0x8B51, // GL_FLOAT_VEC3
		FVEC4 = 0x8B52  // GL_FLOAT_VEC4
	};

	// clang-format on
	// NOLINTEND(CppInconsistentNaming)

	struct ParticleDataInfo final
	{
		ParticleDataType DataType;
		bool Normalized;

		VertexAttributeInfo ConvertToVertexAttribute() const;
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

	private:
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
		if (material != nullptr && !material->CheckParticleCompatibility(GpuParticle::GetParticleStructure()))
		{
			throw IncompatibleMaterialException(false);
		}

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
				m_NextUnusedIndex = std::min(i, m_NextUnusedIndex);
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
		const Quad& quad = assetManager.GetQuad();
		renderBackend.DrawElementsInstanced(m_ParticleVao, quad.GetEbo(), 6, m_LastUsedIndex + 1);
	}

	template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
	void ParticleSystem<CpuParticle, GpuParticle, ParticleSpawnData>::Init()
	{
		RenderBackend& renderBackend = RenderBackend::Get();

		m_CpuParticles.resize(m_MaxParticles);
		m_GpuParticles.resize(m_MaxParticles);

		renderBackend.GenerateVertexArray(m_ParticleVao);

		const AssetManager& assetManager = AssetManager::Get();
		const Quad& quad = assetManager.GetQuad();

		// Bind the quad EBO and VBO and setup the attributes
		renderBackend.BindBuffer(quad.GetEbo(), BufferType::ElementArrayBuffer);
		renderBackend.BindBuffer(quad.GetVbo(), BufferType::ArrayBuffer);
		quad.SetupQuadVertexAttributes();

		renderBackend.GenerateBuffer(m_ParticleVbo, BufferType::ArrayBuffer);
		renderBackend.SetBufferData(m_ParticleVbo, BufferType::ArrayBuffer, BufferDrawType::StreamDraw, m_MaxParticles * sizeof(GpuParticle), nullptr);

		const auto particleStructure = GpuParticle::GetParticleStructure();
		u32 index = 2;
		u32 offset = 0;

		for (const auto& particleData : particleStructure)
		{
			VertexAttributeInfo vertexAttributeInfo = particleData.ConvertToVertexAttribute();

			renderBackend.SetVertexAttributePointerForInstancing(index, vertexAttributeInfo.DataSize, vertexAttributeInfo.DataType, particleData.Normalized, sizeof(GpuParticle), offset);

			index++;
			offset += vertexAttributeInfo.ByteSize;
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
