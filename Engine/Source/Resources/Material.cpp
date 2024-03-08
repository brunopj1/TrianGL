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
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    ASSERT_SINGLETON_USAGE(Engine::Services::ResourceManager, Engine::Resources::Material, false);

    Services::ResourceManager::UnloadShader(m_Shader);

    for (const auto attribute : m_Attributes)
    {
        delete attribute;
    }
}

void Engine::Resources::Material::OnRenderSetup() const
{}

Engine::Resources::TextureMaterialAttribute* Engine::Resources::Material::AddTextureAttribute(const std::string& name, const unsigned int slot, const bool ignoreIfInvalid)
{
    const int location = m_Shader->GetUniformLocation(name);

    if (ignoreIfInvalid && location == -1)
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
    m_PvmMatrix = AddAttribute<Mat4MaterialAttribute>("uPVMMatrix", true);
}

void Engine::Resources::Material::UpdateEngineAttributes(const glm::mat4& modelMatrix) const
{
    const Entities::Camera* camera = Entities::Camera::GetMainCamera();

    if (m_PvmMatrix != nullptr)
    {
        const auto pvmMatrix = camera->GetProjectionViewMatrix() * modelMatrix;
        m_PvmMatrix->SetValue(pvmMatrix);
    }
}
