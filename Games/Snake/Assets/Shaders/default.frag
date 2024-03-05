#version 430 core

uniform sampler2D uMainTexture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(uMainTexture, TexCoord);
}