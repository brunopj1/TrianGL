#pragma once

#include "Internal/Shader.h"
#include "MaterialUniforms.h"
#include "Util/Macros/MaterialMacros.hpp"
#include "Util/Macros/SpawnerMacros.hpp"
#include <memory>
#include <string>
#include <vector>

// Forward declarat
namespace TGL
{
    class Material : public std::enable_shared_from_this<Material>
    {
    private:
        friend class ResourceManager;
        friend class TextureRenderer;

    private:
        DECLARE_SPAWNER_USAGE_VAR();

    private:
        Shader* m_Shader;
        std::vector<MaterialUniform*> m_Uniforms;
        unsigned char m_NextTextureSlot = 0;

    private:
        Mat4Uniform* m_PvmMatrix;
        Mat4Uniform* m_ModelMatrix;

    public:
        Material(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        virtual ~Material();

    public:
        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
        Material(Material&&) = delete;
        Material& operator=(Material&&) = delete;

    protected:
        virtual void OnRenderSetup() const;

    public:
        template <typename T, typename = std::enable_if_t<std::is_base_of_v<Material, T>>>
        std::shared_ptr<T> As()
        {
            return std::dynamic_pointer_cast<T>(shared_from_this());
        }

    public:
        template <typename T, typename... Args, typename = SPAWNER_TEMPLATE_CONDITION(TGL::Material)>
        static std::shared_ptr<T> CreateInstanceOf(Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
        {
            PREPARE_SPAWNER_USAGE(TGL::Material);

            std::shared_ptr<T> instance = std::make_shared<T>(std::forward<Args>(args)...);

            return instance;
        }

    protected:
        template <typename T, typename = std::enable_if_t<!std::is_same_v<MaterialUniform, T> && std::is_base_of_v<MaterialUniform, T> && std::is_constructible_v<T, int>>>
        T* AddUniform(const std::string& name, const bool createIfInvalid = true)
        {
            const int location = m_Shader->GetUniformLocation(name);

            if (location == -1 && !createIfInvalid)
            {
                return nullptr;
            }

            PREPARE_SPAWNER_USAGE(TGL::MaterialUniform);

            T* uniform = new T(location);

            if (location != -1)
            {
                m_Uniforms.push_back(uniform);
            }

            return uniform;
        }

        TextureUniform* AddTextureUniform(const std::string& name, bool createIfInvalid = true);

    private:
        void Use(const glm::mat4& modelMatrix) const;

        void CreateEngineUniforms();
        void UpdateEngineUniforms(const glm::mat4& modelMatrix) const;
    };
}
