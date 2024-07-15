#include "Quad.h"

#include <glad/glad.h>

using namespace TGL;

void Quad::Init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // @formatter:off

    constexpr f32 vertices[] = {
        // Positions     // Tex Coords
        -0.5f, -0.5f,    0.0f, 0.0f,    // Bottom Left
         0.5f, -0.5f,    1.0f, 0.0f,    // Bottom Right
        -0.5f,  0.5f,    0.0f, 1.0f,    // Top Left
         0.5f,  0.5f,    1.0f, 1.0f     // Top Right
    };

    constexpr u32 indices[] = {
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

    BindAttributes();

    glBindVertexArray(0);
}

void Quad::Terminate()
{
    glDeleteBuffers(1, &s_QuadVbo);
    s_QuadVbo = 0;

    glDeleteBuffers(1, &s_QuadEbo);
    s_QuadEbo = 0;

    glDeleteVertexArrays(1, &s_QuadVao);
    s_QuadVao = 0;
}

void Quad::BindAttributes()
{
    // ReSharper disable once CppCStyleCast, CppZeroConstantCanBeReplacedWithNullptr
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    // ReSharper disable once CppCStyleCast, performance-no-int-to-ptr
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(f32)));
    glEnableVertexAttribArray(1);
}
