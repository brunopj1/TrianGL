#include "Quad.h"

#include "Core/Internal/RenderLayer.h"

using namespace TGL;

void Quad::Init()
{
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

    RenderLayer::GenerateVertexArray(s_QuadVao);
    
    RenderLayer::GenerateBuffer(s_QuadVbo, BufferType::ArrayBuffer);
    RenderLayer::SetBufferData(s_QuadVbo, BufferType::ArrayBuffer, BufferDrawType::StaticDraw, sizeof(vertices), vertices);
    
    RenderLayer::GenerateBuffer(s_QuadEbo, BufferType::ElementArrayBuffer);
    RenderLayer::SetBufferData(s_QuadEbo, BufferType::ElementArrayBuffer, BufferDrawType::StaticDraw, sizeof(indices), indices);

    SetupVertexAttributes();
    
    RenderLayer::UnbindVertexArray();
}

void Quad::Terminate()
{
    RenderLayer::DeleteBuffer(s_QuadVbo);
    s_QuadVbo = 0;

    RenderLayer::DeleteBuffer(s_QuadEbo);
    s_QuadEbo = 0;

    RenderLayer::DeleteVertexArray(s_QuadVao);
    s_QuadVao = 0;
}

void Quad::SetupVertexAttributes()
{
    RenderLayer::SetVertexAttributePointer(0, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 0);
    RenderLayer::SetVertexAttributePointer(1, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 2 * sizeof(f32));
}
