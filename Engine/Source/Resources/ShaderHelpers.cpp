#include "ShaderHelpers.h"

#include "Shader.h"

using namespace Engine::Resources;

std::size_t ShaderHash::operator()(const Shader* shader) const
{
    const auto hash1 = std::hash<std::string>{}(shader->m_VertexShader);
    const auto hash2 = std::hash<std::string>{}(shader->m_FragmentShader);

    // Combine the hash values using a simple hash function
    return hash1 ^ hash2;
}

bool ShaderEqual::operator()(const Shader* shader1, const Shader* shader2) const
{
    return shader1->m_IsFilePath == shader2->m_IsFilePath &&
        shader1->m_VertexShader == shader2->m_VertexShader &&
        shader1->m_FragmentShader == shader2->m_FragmentShader;
}
