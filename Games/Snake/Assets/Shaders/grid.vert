#version 430 core

uniform mat4 uPVMMatrix;
uniform mat4 uModelMatrix;

uniform uvec2 uGridSize;
uniform float uEdgeWidth;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    // Offset the position by uEdgeWidth * 0.5 (in world space)
    float offsetX = uEdgeWidth / uGridSize.x * 0.5;
    float offsetY = uEdgeWidth / uGridSize.y * 0.5;

    vec3 offset = vec3(offsetX, offsetY, 0) * vec3(aTexCoord * 2 - 1, 1);

    gl_Position = uPVMMatrix * vec4(aPos + offset, 1.0);
    TexCoord = aTexCoord;
}