#pragma once

#include "Core/DataTypes.h"
#include "Internal/Macros/ClassMacros.h"
#include <Assets/Internal/Shader.h>
#include <Assets/MaterialUniforms.h>
#include <Core/Services/Internal/AssetManager.h>
#include <Internal/Concepts/MaterialConcepts.h>
#include <Memory/SharedPtr.h>
#include <string>
#include <vector>

// Forward declarations
namespace TGL
{
	class Material
	{
	private:
		friend class AssetManager;
		friend class SpriteRenderer;
		friend class ParticleSystem;

	private:
		Shader* m_Shader;
		std::vector<MaterialUniform*> m_Uniforms;
		u8 m_NextTextureSlot = 0;

	private:
		Mat4Uniform* m_PvmMatrix;
		Mat4Uniform* m_ProjectionMatrix;
		Mat4Uniform* m_ViewMatrix;
		Mat4Uniform* m_ModelMatrix;

	public:
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual ~Material();

	public:
		DELETE_COPY_AND_MOVE_CONSTRUCTORS(Material);

	protected:
		virtual void OnRenderSetup() const;

	public:
		template <typename T, typename... Args>
			requires SpawnableMaterial<T, Args...>
		static SharedPtr<T> CreateInstanceOf(Args&&... args);

	protected:
		template <SpawnableMaterialUniform T>
		T* AddUniform(const std::string& name, bool createIfInvalid = true);

	private:
		void Use(const glm::mat4& modelMatrix) const;

		void CreateEngineUniforms();
		void UpdateEngineUniforms(const glm::mat4& modelMatrix) const;
	};

	// Template definitions

	template <typename T, typename... Args>
		requires SpawnableMaterial<T, Args...>
	SharedPtr<T> Material::CreateInstanceOf(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		AssetManager& assetManager = AssetManager::Get();
		return assetManager.LoadMaterial<T>(std::forward<Args>(args)...);
	}

	template <SpawnableMaterialUniform T>
	T* Material::AddUniform(const std::string& name, const bool createIfInvalid)
	{
		AssetManager& assetManager = AssetManager::Get();
		return assetManager.CreateMaterialUniform<T>(name, createIfInvalid, m_Shader, m_NextTextureSlot, m_Uniforms);
	}
}
