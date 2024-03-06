#version 430 core

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform int uIsTextureValid;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    if (uIsTextureValid == 0) 
    {
        FragColor = uColor;
    }  
    else
    {
        FragColor = texture(uTexture, TexCoord) * uColor;
    }
}