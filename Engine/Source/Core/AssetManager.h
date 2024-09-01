#pragma once

#include "Service.h"
#include <Assets/Internal/Shader.h>
#include <Internal/Concepts/MaterialConcepts.h>
#include <Internal/Asserts/SpawnerAsserts.h>
#include <Memory/SharedPtr.h>

#include <string>
#include <memory>
#include <unordered_map>

// Forward declarations
namespace SoLoud
{
    class Soloud;
}

namespace TGL
{
    // Forward declarations
    struct TextureParameters;

    class AssetManager : public Service<AssetManager>
    {
    private:
        friend class Application;

        friend class Texture;
        friend class TextureSlice;
        friend class Audio;
        friend class Material;
        friend class MaterialUniform;

        friend class SpriteRenderer;
        friend class ParticleSystem;
        friend class AudioPlayer;
        
        friend class ReferenceCounter;

        template <typename T>
        friend class SharedPtr;

    private:
        DECLARE_SPAWNER_ASSERT_VAR(Texture);
        DECLARE_SPAWNER_ASSERT_VAR(TextureSlice);
        DECLARE_SPAWNER_ASSERT_VAR(Audio);
        DECLARE_SPAWNER_ASSERT_VAR(Material);
        DECLARE_SPAWNER_ASSERT_VAR(MaterialUniform);

    private:
        u32 m_QuadVao = 0;
        u32 m_QuadVbo = 0;
        u32 m_QuadEbo = 0;
        
        std::unordered_map<Shader*, u32, ShaderHash, ShaderEqual> m_Shaders;
        
        SoLoud::Soloud* m_SoloudEngine = nullptr;

    private:
        AssetManager() = default;
        ~AssetManager() = default;

    private:
        void Init();
        void Terminate();

    private:
        void InitQuad();
        void SetupQuadVertexAttributes() const;
        void TerminateQuad();

        u32 GetQuadVao() const;
        u32 GetQuadVbo() const;
        u32 GetQuadEbo() const;

    private:
        SharedPtr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);
        SharedPtr<TextureSlice> CreateTextureSlice(SharedPtr<Texture> texture, i32 index);
        void UnloadTexture(Texture* texture);

    private:
        SharedPtr<Audio> LoadAudio(const std::string& filePath, bool stream);
        void UnloadAudio(Audio* audio);

    private:
        template <typename T, typename... Args> requires SpawnableMaterial<T, Args...>
        SharedPtr<T> LoadMaterial(Args&&... args);

        template <SpawnableMaterialUniform T>
        T* CreateMaterialUniform(const std::string& name, bool createIfInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& uniformVector);

        void UnloadMaterialUniforms(const Material* material);

    private:
        Shader* LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        void UnloadShader(Shader* shader);
    };

    // Template definitions

    template <typename T, typename... Args> requires SpawnableMaterial<T, Args...>
    SharedPtr<T> AssetManager::LoadMaterial(Args&&... args) // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        PREPARE_SPAWNER_ASSERT(Material);

        T* instance = new T(std::forward<Args>(args)...);

        return instance;
    }

    template <SpawnableMaterialUniform T>
    T* AssetManager::CreateMaterialUniform(const std::string& name, const bool createIfInvalid, const Shader* shader, u8& nextTextureSlot, std::vector<MaterialUniform*>& uniformVector)
    {
        // No need to assert here since this doesn't interact with OpenGL

        PREPARE_SPAWNER_ASSERT(MaterialUniform);

        T* instance = new T(shader, name);

        if constexpr (std::is_same_v<T, SpriteUniform>)
        {
            if (instance->m_Location != -1) instance->m_Slot = nextTextureSlot++;
        }

        if (instance->IsValid())
        {
            uniformVector.push_back(instance);
        }
        else if (!createIfInvalid)
        {
            PREPARE_SPAWNER_ASSERT(MaterialUniform);

            delete instance;
            instance = nullptr;
        }

        return instance;
    }
}
