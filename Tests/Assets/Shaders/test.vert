#version 430 core

uniform mat4 uPVMMatrix;

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = uPVMMatrix * vec4(aPos, 0.0, 1.0);
    texCoord = aTexCoord;
}