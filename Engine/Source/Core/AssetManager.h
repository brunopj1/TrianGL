#pragma once

#include "Assets/Internal/Shader.h"
#include "Util/Macros/MaterialMacros.h"
#include "Util/Macros/SingletonMacros.h"
#include "Util/Macros/SpawnerMacros.h"
#include "Util/Memory/SharedPtr.h"

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

    class AssetManager
    {
    private:
        friend class Application;

        friend class Texture;
        friend class TextureSlice;
        friend class Audio;
        friend class Material;
        friend class MaterialUniform;

        friend class AudioPlayer;

        friend class ReferenceCounter;

    private:
        DECLARE_SPAWNER_USAGE_VAR(Texture);
        DECLARE_SPAWNER_USAGE_VAR(TextureSlice);
        DECLARE_SPAWNER_USAGE_VAR(Audio);
        DECLARE_SPAWNER_USAGE_VAR(Material);
        DECLARE_SPAWNER_USAGE_VAR(MaterialUniform);

    private:
        static inline bool s_CanCreateAndDestroyObjects = false;

    private:
        static inline SoLoud::Soloud* s_SoloudEngine = nullptr;

    private:
        static inline std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> s_Shaders;
        
    public:
        AssetManager() = delete;
        ~AssetManager() = delete;

    private:
        static void Init();
        static void Terminate();

    private:
        static SharedPtr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);

        static SharedPtr<TextureSlice> CreateTextureSlice(SharedPtr<Texture> texture, int index);

        static void UnloadTexture(Texture* texture);

    private:
        static SharedPtr<Audio> LoadAudio(const std::string& filePath, bool stream);

        static void UnloadAudio(Audio* audio);

    private:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Material)>
        static SharedPtr<T> LoadMaterial(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_OBJECT_CREATION();

            PREPARE_SPAWNER_USAGE(Material);

            T* instance = new T(std::forward<Args>(args)...);

            return instance;
        }

        template <typename T, typename = UNIFORM_TEMPLATE_SPAWN_CONDITION>
        static T* CreateMaterialUniform(const std::string& name, const bool createIfInvalid, const Shader* shader, unsigned char& nextTextureSlot, std::vector<MaterialUniform*>& uniformVector)
        {
            // No need to assert here since this doesn't interact with OpenGL

            PREPARE_SPAWNER_USAGE(MaterialUniform);

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
                PREPARE_SPAWNER_USAGE(MaterialUniform);

                delete instance;
                instance = nullptr;
            }

            return instance;
        }

        static void UnloadMaterialUniforms(const Material* material);

    private:
        static Shader* LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        static void UnloadShader(Shader* shader);
    };
}
