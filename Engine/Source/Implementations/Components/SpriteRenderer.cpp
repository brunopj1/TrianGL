﻿#include "SpriteRenderer.h"

#include "Game/Entity.h"
#include "glad/glad.h"
#include "Resources/Material.h"
#include "Implementations/Resources/DefaultMaterial.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

SpriteRenderer::SpriteRenderer(std::shared_ptr<Material> material)
    : Component(false), m_Material(std::move(material))
{}

std::shared_ptr<Material> SpriteRenderer::GetMaterial() const
{
    return m_Material;
}

void SpriteRenderer::SetMaterial(std::shared_ptr<Material> material)
{
    m_Material = std::move(material);
}

std::shared_ptr<DefaultMaterial> SpriteRenderer::UseDefaultMaterial()
{
    auto defaultMaterial = Material::CreateInstanceOf<DefaultMaterial>();
    m_Material = defaultMaterial;
    return defaultMaterial;
}

glm::vec2 SpriteRenderer::GetPivot() const
{
    return m_Pivot;
}

void SpriteRenderer::SetPivot(const glm::vec2& pivot)
{
    m_Pivot = pivot;
}

void SpriteRenderer::Init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

void SpriteRenderer::Terminate()
{
    glDeleteBuffers(1, &s_QuadVbo);
    s_QuadVbo = 0;

    glDeleteBuffers(1, &s_QuadEbo);
    s_QuadEbo = 0;

    glDeleteVertexArrays(1, &s_QuadVao);
    s_QuadVao = 0;
}

void SpriteRenderer::Render()
{
    if (m_Material == nullptr) return;

    const glm::mat4 parentModelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 rendererModelMatrix = GetTransform().GetTransformMatrix();

    glm::mat4 modelMatrix = parentModelMatrix * rendererModelMatrix;

    if (m_Pivot != glm::vec2(0.5f))
    {
        const glm::vec3 sign = glm::sign(glm::vec3(modelMatrix[0][0], modelMatrix[1][1], 1));

        modelMatrix = translate(modelMatrix, glm::vec3(0.5f - m_Pivot, 0.0f) * sign);
    }

    if (const int zIndex = GetZIndex(); zIndex != 0)
    {
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<float>(zIndex)));
    }

    m_Material->Use(modelMatrix);

    glBindVertexArray(s_QuadVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadEbo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}