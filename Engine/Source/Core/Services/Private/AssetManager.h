#pragma once

#include "Assets/MaterialUniforms.h"
#include <Assets/Internal/Shader.h>
#include <Core/Service.h>
#include <Internal/Asserts/SpawnerAsserts.h>
#include <Internal/Concepts/MaterialConcepts.h>
#include <Memory/SharedPtr.h>
#include <memory>
#include <stdexcept>
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
		friend class Audio;
		friend class Material;
		friend class MaterialUniform;
		friend class Texture;
		friend class TextureSlice;

		friend class SpriteRenderer;
		friend class ParticleSystem;
		friend class AudioPlayer;

		friend class ReferenceCounter;

		template <typename T>
		friend class SharedPtr;

	private:
		DECLARE_SPAWNER_EXPECT_VAR(Animation);
		DECLARE_SPAWNER_EXPECT_VAR(AnimationFrame);
		DECLARE_SPAWNER_EXPECT_VAR(Audio);
		DECLARE_SPAWNER_EXPECT_VAR(Material);
		DECLARE_SPAWNER_EXPECT_VAR(MaterialUniform);
		DECLARE_SPAWNER_EXPECT_VAR(Texture);
		DECLARE_SPAWNER_EXPECT_VAR(TextureSlice);

	protected:
		u32 m_QuadVao = 0;
		u32 m_QuadVbo = 0;
		u32 m_QuadEbo = 0;

		std::unordered_map<Shader*, u32, ShaderHash, ShaderEqual> m_Shaders;

		SoLoud::Soloud* m_SoloudEngine = nullptr;

	protected:
		AssetManager() = default;
		MOCKABLE_DESTRUCTOR ~AssetManager() = default;

	protected:
		MOCKABLE_METHOD void Init();
		MOCKABLE_METHOD void Terminate();

	protected:
		MOCKABLE_METHOD void InitQuad();
		MOCKABLE_METHOD void SetupQuadVertexAttributes() const;
		MOCKABLE_METHOD void TerminateQuad();

		MOCKABLE_METHOD u32 GetQuadVao() const;
		MOCKABLE_METHOD u32 GetQuadVbo() const;
		MOCKABLE_METHOD u32 GetQuadEbo() const;

	protected:
		MOCKABLE_METHOD SharedPtr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);
		MOCKABLE_METHOD SharedPtr<TextureSlice> CreateTextureSlice(SharedPtr<Texture> texture, i32 index);

	protected:
		MOCKABLE_METHOD SharedPtr<Animation> CreateAnimation();
		MOCKABLE_METHOD SharedPtr<AnimationFrame> CreateAnimationFrame(Animation* animation, SharedPtr<Sprite> sprite, f32 duration);

	protected:
		MOCKABLE_METHOD SharedPtr<Audio> LoadAudio(const std::string& filePath, bool stream);

	protected:
		template <typename T, typename... Args>
			requires SpawnableMaterial<T, Args...>
		SharedPtr<T> LoadMaterial(Args&&... args);

		template <SpawnableMaterialUniform T>
		T* CreateMaterialUniform(const std::string& name, bool createIfInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& validUniforms, std::vector<MaterialUniform*>& invalidUniforms);

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
		PREPARE_SPAWNER_ASSERT(Material);

		T* instance = new T(std::forward<Args>(args)...);

		return instance;
	}

	template <SpawnableMaterialUniform T>
	T* AssetManager::CreateMaterialUniform(const std::string& name, const bool createIfInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& validUniforms, std::vector<MaterialUniform*>& invalidUniforms)
	{
		// TODO add option to throw an exception if the uniform is invalid
		// TODO ensure that the uniform data type and size are correct (and add unit tests)

		PREPARE_SPAWNER_ASSERT(MaterialUniform);

		T* instance = new T(shader, name);

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
		else if (createIfInvalid)
		{
			invalidUniforms.push_back(instance);
		}
		else
		{
			PREPARE_SPAWNER_ASSERT(MaterialUniform);

			delete instance;
			instance = nullptr;
		}

		return instance;
	}
}
