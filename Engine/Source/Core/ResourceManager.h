#pragma once

#include "Resources/Internal/Shader.h"
#include "Util/Macros/MaterialMacros.h"
#include "Util/Macros/SingletonMacros.h"
#include "Util/Macros/SpawnerMacros.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace TGL
{
    // Forward declarations
    struct TextureParameters;
    class TextureSlice;

    class ResourceManager
    {
    private:
        friend class Application;
        friend class Texture;
        friend class TextureSlice;
        friend class Material;
        friend class MaterialUniform;

    private:
        DECLARE_SINGLETON_INSTANCE_VAR(TGL::ResourceManager);

    private:
        DECLARE_SPAWNER_USAGE_VAR(Texture);
        DECLARE_SPAWNER_USAGE_VAR(TextureSlice);
        DECLARE_SPAWNER_USAGE_VAR(Material);
        DECLARE_SPAWNER_USAGE_VAR(MaterialUniform);

    private:
        std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> m_Shaders;

    private:
        ResourceManager();
        ~ResourceManager();

    private:
        static std::shared_ptr<Texture> LoadTexture(const std::string& filePath, const TextureParameters& parameters);

        static void UnloadTexture(Texture* texture);

        static std::shared_ptr<TextureSlice> CreateTextureSlice(Texture* texture, int index);

        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Material)>
        static std::shared_ptr<T> LoadMaterial(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE(Material);

            std::shared_ptr<T> instance = std::make_shared<T>(std::forward<Args>(args)...);

            return instance;
        }

        template <typename T, typename = UNIFORM_TEMPLATE_SPAWN_CONDITION>
        static T* CreateMaterialUniform(const std::string& name, const bool createIfInvalid, const Shader* shader, unsigned char& nextTextureSlot, std::vector<MaterialUniform*>& uniformVector)
        {
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

        static Shader* LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        static void UnloadShader(Shader* shader);
    };
}
