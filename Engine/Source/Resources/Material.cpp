#include "Material.h"

#include "MaterialAttributes.h"
#include "Shader.h"
#include "Services/ResourceManager.h"
#include "Entities/Camera.h"
#include "Util/Macros/SingletonMacros.hpp"

Engine::Resources::Material::Material(const std::string& vertexShader, const std::string& fragmentShader, const bool isFilePath)
{
    ASSERT_SINGLETON_USAGE(Engine::Services::ResourceManager, Engine::Resources::Material, true);

    m_Shader = Services::ResourceManager::LoadShader(vertexShader, fragmentShader, isFilePath);

    CreateEngineAttributes();
}

Engine::Resources::Material::~Material()
{
    ASSERT_SINGLETON_USAGE(Engine::Services::ResourceManager, Engine::Resources::Material, false);

    Services::ResourceManager::UnloadShader(m_Shader);

    for (const auto attribute : m_Attributes)
    {
        delete attribute;
    }
}

void Engine::Resources::Material::OnRenderSetup() const
{}

Engine::Resources::TextureMaterialAttribute* Engine::Resources::Material::AddTextureAttribute(const std::string& name, const unsigned int slot, const bool createIfInvalid)
{
    const int location = m_Shader->GetUniformLocation(name);

    if (location == -1 && !createIfInvalid)
    {
        return nullptr;
    }

    const auto attribute = new TextureMaterialAttribute(location, slot);

    if (location != -1)
    {
        m_Attributes.push_back(attribute);
    }

    return attribute;
}

void Engine::Resources::Material::Use(const glm::mat4& modelMatrix) const
{
    m_Shader->Use();

    UpdateEngineAttributes(modelMatrix);

    for (const auto attribute : m_Attributes)
    {
        attribute->Bind();
    }
}

void Engine::Resources::Material::CreateEngineAttributes()
{
    m_PvmMatrix = AddAttribute<Mat4MaterialAttribute>("uPVMMatrix", false);
    m_ModelMatrix = AddAttribute<Mat4MaterialAttribute>("uModelMatrix", false);
}

void Engine::Resources::Material::UpdateEngineAttributes(const glm::mat4& modelMatrix) const
{
    const Entities::Camera* camera = Entities::Camera::GetMainCamera();
    // Null checking is not needed since the game is not rendered without a camera

    if (m_PvmMatrix != nullptr)
    {
        const auto pvmMatrix = camera->GetProjectionViewMatrix() * modelMatrix;
        m_PvmMatrix->SetValue(pvmMatrix);
    }

    if (m_ModelMatrix != nullptr)
    {
        m_ModelMatrix->SetValue(modelMatrix);
    }
}
