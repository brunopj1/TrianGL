#version 430 core

uniform mat4 uPVMMatrix;
uniform mat4 uModelMatrix;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = uPVMMatrix * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}