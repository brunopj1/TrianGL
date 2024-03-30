#pragma once

#include "Resources/Internal/Shader.h"
#include "Util/Macros/MaterialMacros.h"
#include "Util/Macros/SingletonMacros.h"
#include "Util/Macros/SpawnerMacros.h"

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

    class ResourceManager
    {
    private:
        friend class Application;

        friend class Texture;
        friend class TextureSlice;
        friend class Sound;
        friend class Material;
        friend class MaterialUniform;

        friend class AudioPlayer;

    private:
        DECLARE_SPAWNER_USAGE_VAR(Texture);
        DECLARE_SPAWNER_USAGE_VAR(TextureSlice);
        DECLARE_SPAWNER_USAGE_VAR(Sound);
        DECLARE_SPAWNER_USAGE_VAR(Material);
        DECLARE_SPAWNER_USAGE_VAR(MaterialUniform);

    private:
        static inline bool s_CanCreateAndDestroyObjects = false;

    private:
        static inline SoLoud::Soloud* s_SoloudEngine = nullptr;

    private:
        static inline std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> s_Shaders;

    public:
        ResourceManager() = delete;
        ~ResourceManager() = delete;

    private:
        static void Init();
        static void Terminate();

    private:
        static std::shared_ptr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);

        static std::shared_ptr<TextureSlice> CreateTextureSlice(Texture* texture, int index);

        static void UnloadTexture(Texture* texture);

    private:
        static std::shared_ptr<Sound> LoadSound(const std::string& filePath);

        static void UnloadSound(Sound* sound);

    private:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Material)>
        static std::shared_ptr<T> LoadMaterial(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            ASSERT_SINGLETON_OBJECT_CREATION();

            PREPARE_SPAWNER_USAGE(Material);

            std::shared_ptr<T> instance = std::make_shared<T>(std::forward<Args>(args)...);

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
