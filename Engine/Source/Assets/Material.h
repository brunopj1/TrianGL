#pragma once

#include "Core/DataTypes.h"
#include "Core/Internal/Macros/ClassMacros.h"
#include <Assets/Internal/Shader.h>
#include <Assets/MaterialUniforms.h>
#include <Core/Internal/Concepts/MaterialConcepts.h>
#include <Core/Services/Private/AssetManager.h>
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
		std::vector<MaterialUniform*> m_ValidUniforms;
		std::vector<MaterialUniform*> m_InvalidUniforms;
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
		virtual void OnRenderSetup();

	public:
		template <typename T, typename... Args>
			requires SpawnableMaterial<T, Args...>
		static SharedPtr<T> CreateInstanceOf(Args&&... args);

	public:
		template <SpawnableMaterialUniform T>
		T* AddUniform(const std::string& name, OnInvalidUniform onInvalid = OnInvalidUniform::Create);

	private:
		void Use(const glm::mat4& modelMatrix);

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
	T* Material::AddUniform(const std::string& name, const OnInvalidUniform onInvalid)
	{
		AssetManager& assetManager = AssetManager::Get();
		return assetManager.CreateMaterialUniform<T>(name, onInvalid, m_Shader, m_NextTextureSlot, m_ValidUniforms, m_InvalidUniforms);
	}
}
