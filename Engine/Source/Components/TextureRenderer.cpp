#include "TextureRenderer.h"

#include "Game/Entity.h"
#include "glad/glad.h"
#include <iostream>

using namespace Engine::Components;

TextureRenderer::TextureRenderer()
    : Component(false)
{}

void TextureRenderer::Initialize()
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

    constexpr const char* vertexShaderSource = R"(
        #version 430 core

        uniform mat4 uPVMMatrix;

        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        void main()
        {
            gl_Position = uPVMMatrix * vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    constexpr const char* fragmentShaderSource = R"(
        #version 430 core

        in vec2 TexCoord;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(TexCoord, 0.0, 1.0);
        }
    )";

    s_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_VertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(s_VertexShader);

    s_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_FragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(s_FragmentShader);

    s_ShaderProgram = glCreateProgram();
    glAttachShader(s_ShaderProgram, s_VertexShader);
    glAttachShader(s_ShaderProgram, s_FragmentShader);
    glLinkProgram(s_ShaderProgram);
}

void TextureRenderer::Terminate()
{
    glDeleteBuffers(1, &s_QuadVbo);
    s_QuadVbo = 0;

    glDeleteBuffers(1, &s_QuadEbo);
    s_QuadEbo = 0;

    glDeleteVertexArrays(1, &s_QuadVao);
    s_QuadVao = 0;

    glDetachShader(s_ShaderProgram, s_VertexShader);
    glDeleteShader(s_VertexShader);

    glDetachShader(s_ShaderProgram, s_FragmentShader);
    glDeleteShader(s_FragmentShader);

    glDeleteProgram(s_ShaderProgram);
}

void TextureRenderer::Render(const glm::mat4& projectionViewMatrix) const
{
    const glm::mat4 modelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 pvmMatrix = projectionViewMatrix * modelMatrix;

    glUseProgram(s_ShaderProgram);

    if (const int location = glGetUniformLocation(s_ShaderProgram, "uPVMMatrix"); location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &pvmMatrix[0][0]);
    }

    glBindVertexArray(s_QuadVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadEbo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
