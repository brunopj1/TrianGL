#version 430 core

uniform int uIsTextureValid;

uniform sampler2D uTexture;
uniform mat4 uTextureMatrix;

uniform vec4 uColor;

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
        vec2 coord = (uTextureMatrix * vec4(TexCoord, 0.0, 1.0)).xy;
        FragColor = texture(uTexture, coord) * uColor;
    }
}