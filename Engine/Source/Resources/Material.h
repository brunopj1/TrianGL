#pragma once

#include "Internal/Shader.h"
#include "MaterialUniforms.h"
#include "Core/ResourceManager.h"
#include "Util/Macros/MaterialMacros.h"
#include "Util/Macros/SpawnerMacros.h"
#include <memory>
#include <string>
#include <vector>

// Forward declarations
namespace TGL
{
    class Material : public std::enable_shared_from_this<Material>
    {
    private:
        friend class ResourceManager;
        friend class SpriteRenderer;

    private:
        Shader* m_Shader;
        std::vector<MaterialUniform*> m_Uniforms;
        unsigned char m_NextTextureSlot = 0;

    private:
        Mat4Uniform* m_PvmMatrix;
        Mat4Uniform* m_ProjectionMatrix;
        Mat4Uniform* m_ViewMatrix;
        Mat4Uniform* m_ModelMatrix;

    public:
        Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
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
            return ResourceManager::LoadMaterial<T>(std::forward<Args>(args)...);
        }

    protected:
        template <typename T, typename = UNIFORM_TEMPLATE_SPAWN_CONDITION>
        T* AddUniform(const std::string& name, const bool createIfInvalid = true)
        {
            return ResourceManager::CreateMaterialUniform<T>(name, createIfInvalid, m_Shader, m_NextTextureSlot, m_Uniforms);
        }

    private:
        void Use(const glm::mat4& modelMatrix) const;

        void CreateEngineUniforms();
        void UpdateEngineUniforms(const glm::mat4& modelMatrix) const;
    };
}
