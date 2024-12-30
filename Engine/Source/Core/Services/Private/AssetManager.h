#pragma once

#include "Assets/Internal/Quad.h"
#include "Assets/MaterialUniforms.h"
#include "Core/Internal/Macros/AssetFactoryMacros.h"
#include "Exceptions/Assets/InvalidMaterialUniformException.h"
#include <Assets/Internal/Shader.h>
#include <Core/Internal/Concepts/MaterialConcepts.h>
#include <Core/Service.h>
#include <Memory/SharedPtr.h>
#include <string>
#include <unordered_map>

// Forward declarations
namespace SoLoud
{
	class Soloud;
}

// TODO create a class for the quad again

namespace TGL
{
	// Forward declarations
	struct TextureParameters;

	class AssetManager : public Service<AssetManager>
	{
	private:
		friend class Application;
		friend class ServiceCollection;
		friend struct ServiceDeleter<AssetManager>;

		friend class Animation;
		friend class AnimationFrame;
		friend class AnimationSprite;
		friend class Audio;
		friend class Material;
		friend class MaterialUniform;
		friend class Shader;
		friend class Texture;
		friend class TextureSlice;

		friend class SpriteRenderer;
		friend class AudioPlayer;
		friend class Animator;

		template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
		friend class ParticleSystem;

		friend class ReferenceCounter;

		template <typename T>
		friend class SharedPtr;

	private:
		DECLARE_ASSET_FACTORY_VAR(Animation);
		DECLARE_ASSET_FACTORY_VAR(AnimationFrame);
		DECLARE_ASSET_FACTORY_VAR(AnimationSprite);
		DECLARE_ASSET_FACTORY_VAR(Audio);
		DECLARE_ASSET_FACTORY_VAR(Material);
		DECLARE_ASSET_FACTORY_VAR(MaterialUniform);
		DECLARE_ASSET_FACTORY_VAR(Texture);
		DECLARE_ASSET_FACTORY_VAR(TextureSlice);

	protected:
		Quad m_Quad;
		std::unordered_map<Shader*, u32, ShaderHash, ShaderEqual> m_Shaders;
		SoLoud::Soloud* m_SoloudEngine = nullptr;

	protected:
		// This constructor is not implicitly deleted, but for some reason my IDE thinks it is
		AssetManager() = default; // NOLINT(CppDefaultedSpecialMemberFunctionIsImplicitlyDeleted)
		MOCKABLE_DESTRUCTOR ~AssetManager() = default;

	protected:
		MOCKABLE_METHOD void Init();
		MOCKABLE_METHOD void Terminate();

	protected:
		MOCKABLE_METHOD const Quad& GetQuad() const;

	protected:
		MOCKABLE_METHOD SharedPtr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);
		MOCKABLE_METHOD SharedPtr<TextureSlice> CreateTextureSlice(SharedPtr<Texture> texture, i32 index);

	protected:
		MOCKABLE_METHOD SharedPtr<Animation> CreateAnimation();
		MOCKABLE_METHOD SharedPtr<AnimationFrame> CreateAnimationFrame(Animation* animation, SharedPtr<Sprite> sprite, f32 duration);

	protected:
		MOCKABLE_METHOD SharedPtr<AnimationSprite> CreateAnimationSprite();

	protected:
		MOCKABLE_METHOD SharedPtr<Audio> LoadAudio(const std::string& filePath, bool stream);

	protected:
		template <typename T, typename... Args>
			requires SpawnableMaterial<T, Args...>
		SharedPtr<T> LoadMaterial(Args&&... args);

		template <SpawnableMaterialUniform T>
		T* CreateMaterialUniform(const std::string& name, OnInvalidUniform onInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& validUniforms, std::vector<MaterialUniform*>& invalidUniforms);

		MOCKABLE_METHOD void UnloadMaterialUniforms(const Material* material);

	protected:
		MOCKABLE_METHOD Shader* LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		MOCKABLE_METHOD void UnloadShader(Shader* shader);
	};

	// Template definitions

	template <typename T, typename... Args>
		requires SpawnableMaterial<T, Args...>
	SharedPtr<T> AssetManager::LoadMaterial(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
	{
		PREPARE_ASSET_FACTORY_CONSTRUCTOR(Material);

		T* instance = new T(std::forward<Args>(args)...);

		ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(Material);

		return instance;
	}

	template <SpawnableMaterialUniform T>
	T* AssetManager::CreateMaterialUniform(const std::string& name, const OnInvalidUniform onInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& validUniforms, std::vector<MaterialUniform*>& invalidUniforms)
	{
		// TODO ensure that the uniform data type and size are correct (and add unit tests)

		PREPARE_ASSET_FACTORY_CONSTRUCTOR(MaterialUniform);

		T* instance = new T(shader, validUniforms, name);

		ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(MaterialUniform);

		if constexpr (std::is_same_v<T, SpriteUniform>)
		{
			if (instance->m_Location != -1)
			{
				instance->m_Slot = nextTextureSlot++;
			}
		}

		if (instance->IsValid())
		{
			validUniforms.push_back(instance);
		}
		else if (onInvalid == OnInvalidUniform::Create)
		{
			invalidUniforms.push_back(instance);
		}
		else
		{
			PREPARE_ASSET_FACTORY_DESTRUCTOR();

			delete instance;
			instance = nullptr;

			ASSERT_POST_ASSET_FACTORY_DESTRUCTOR();

			if (onInvalid == OnInvalidUniform::Throw)
			{
				throw InvalidMaterialUniformException(name);
			}
		}

		return instance;
	}
}
