#include "Material.h"

#include "MaterialAttributes.h"
#include "Shader.h"
#include "Core/ResourceManager.h"
#include "Util/DebugFeatures.hpp"

Engine::Resources::Material::Material(std::string vertexShader, std::string fragmentShader, const bool isFilePath)
    : m_Shader(Shader(std::move(vertexShader), std::move(fragmentShader), isFilePath))
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Material");
}

Engine::Resources::Material::~Material()
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::ResourceManager, "Engine::Resources::Material");

    for (const auto attribute : m_Attributes)
    {
        delete attribute;
    }
}

void Engine::Resources::Material::Use() const
{
    m_Shader.Use();

    for (const auto attribute : m_Attributes)
    {
        attribute->Bind();
    }
}
