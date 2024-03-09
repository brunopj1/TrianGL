#version 430 core

uniform sampler2D uMainTexture;

uniform float uGridResolution = 0.02;

in vec2 WorldPos;

out vec4 FragColor;

void main()
{
    vec2 pos = fract(WorldPos + 0.5);
    
    vec2 bottomLeft = step(uGridResolution * 0.5, pos);
    vec2 topRight = 1 - step(1.0 - uGridResolution * 0.5, pos);
    
    float isGrid = 1 - bottomLeft.x * bottomLeft.y * topRight.x * topRight.y;
    
    //float isGrid = min(pos.x, pos.y);
    
    FragColor = vec4(vec3(0.0), isGrid);
}