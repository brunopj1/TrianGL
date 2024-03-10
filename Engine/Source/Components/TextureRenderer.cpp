#include "TextureRenderer.h"

#include "Game/Entity.h"
#include "glad/glad.h"
#include "Resources/Material.h"
#include "DefaultResources/DefaultMaterial.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine::Components;

TextureRenderer::TextureRenderer(Resources::Material* material)
    : Component(false), m_Material(material)
{}

Engine::Resources::Material* TextureRenderer::GetMaterial() const
{
    return m_Material;
}

void TextureRenderer::SetMaterial(Resources::Material* material, const bool unloadPreviousMaterial)
{
    if (unloadPreviousMaterial && m_Material != nullptr)
    {
        m_Material->Unload();
    }

    m_Material = material;
}

Engine::DefaultResources::DefaultMaterial* TextureRenderer::UseDefaultMaterial(const bool unloadPreviousMaterial)
{
    if (unloadPreviousMaterial && m_Material != nullptr)
    {
        m_Material->Unload();
    }

    const auto material = Resources::Material::Load<DefaultResources::DefaultMaterial>();
    m_Material = material;

    return material;
}

void TextureRenderer::Init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // @formatter:off

    constexpr float vertices[] = {
        // Positions           // Tex Coords
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,    // Bottom Left
         0.5f, -0.5f, 0.0f,    1.0f, 0.0f,    // Bottom Right
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f,    // Top Left
         0.5f,  0.5f, 0.0f,    1.0f, 1.0f     // Top Right
    };

    constexpr unsigned int indices[] = {
        0, 1, 2, // Bottom Left Triangle
        1, 3, 2  // Top Right Triangle
    };

    // @formatter:on

    glGenVertexArrays(1, &s_QuadVao);
    glBindVertexArray(s_QuadVao);

    glGenBuffers(1, &s_QuadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, s_QuadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &s_QuadEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ReSharper disable once CppCStyleCast, performance-no-int-to-ptr
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void TextureRenderer::Terminate()
{
    glDeleteBuffers(1, &s_QuadVbo);
    s_QuadVbo = 0;

    glDeleteBuffers(1, &s_QuadEbo);
    s_QuadEbo = 0;

    glDeleteVertexArrays(1, &s_QuadVao);
    s_QuadVao = 0;
}

void TextureRenderer::Render()
{
    if (m_Material == nullptr) return;

    const glm::mat4 parentModelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 textureModelMatrix = GetTransform().GetTransformMatrix();

    glm::mat4 modelMatrix = parentModelMatrix * textureModelMatrix;

    if (const int zIndex = GetZIndex(); zIndex != 0)
    {
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<float>(zIndex)));
    }

    m_Material->Use(modelMatrix);
    m_Material->OnRenderSetup();

    glBindVertexArray(s_QuadVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadEbo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
