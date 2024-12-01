#version 430 core

uniform int uSize;

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos * uSize, 0.0, 1.0);
    texCoord = aTexCoord;
}