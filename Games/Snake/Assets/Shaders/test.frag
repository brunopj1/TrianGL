#version 430 core

uniform sampler2D uMainTexture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(TexCoord, 0.0, 1.0);
}