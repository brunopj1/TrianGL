#pragma once

#include "Core/DataTypes.h"
#include "Core/Internal/Concepts/ParticleSystemConcepts.h"
#include "ShaderInfo.h"

namespace TGL
{
	class Quad
	{
	public:
		friend class AssetManager;
		friend class Material;

	private:
		friend class SpriteRenderer;
		template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
		friend class ParticleSystem;

	private:
		u32 m_Vao = 0;
		u32 m_Vbo = 0;
		u32 m_Ebo = 0;

	private:
		std::vector<ShaderDataType> m_ShaderAttributes;

	private:
		Quad() = default;
		~Quad() = default;

	private:
		void Init();
		void Terminate();

	private:
		u32 GetVao() const;
		u32 GetVbo() const;
		u32 GetEbo() const;

	private:
		const std::vector<ShaderDataType>& GetShaderAttributes() const;

	private:
		void SetupQuadVertexAttributes() const;
	};
}
