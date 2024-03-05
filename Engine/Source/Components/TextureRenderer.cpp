#include "TextureRenderer.h"

#include "Core/ResourceManager.h"
#include "Game/Entity.h"
#include "glad/glad.h"
#include "Resources/Shader.h"
#include "Resources/Texture.h"
#include <iostream>

using namespace Engine::Components;

TextureRenderer::TextureRenderer()
    : Component(false)
{}

void TextureRenderer::Init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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

    s_Shader = Core::ResourceManager::LoadShader("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");

    Resources::TextureParameters parameters;
    parameters.Filter = Resources::TextureFilterMode::Nearest;
    s_Texture = Core::ResourceManager::LoadTexture("Assets/Textures/ugly_smile.png", parameters);
}

void TextureRenderer::Terminate()
{
    glDeleteBuffers(1, &s_QuadVbo);
    s_QuadVbo = 0;

    glDeleteBuffers(1, &s_QuadEbo);
    s_QuadEbo = 0;

    glDeleteVertexArrays(1, &s_QuadVao);
    s_QuadVao = 0;

    Core::ResourceManager::Unload(s_Shader);
    Core::ResourceManager::Unload(s_Texture);
}

void TextureRenderer::Render(const glm::mat4& projectionViewMatrix) const
{
    if (s_Texture->HasTransparency())
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    const glm::mat4 modelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 pvmMatrix = projectionViewMatrix * modelMatrix;

    s_Shader->Use();

    if (const int location = glGetUniformLocation(s_Shader->m_ProgramId, "uPVMMatrix"); location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &pvmMatrix[0][0]);
    }

    if (const int location = glGetUniformLocation(s_Shader->m_ProgramId, "uMainTexture"); location != -1)
    {
        s_Texture->Bind();
        glUniform1i(location, 0);
    }

    glBindVertexArray(s_QuadVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadEbo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    if (s_Texture->HasTransparency())
    {
        glDisable(GL_BLEND);
    }
}
