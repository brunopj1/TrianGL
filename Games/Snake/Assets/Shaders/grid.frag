#version 430 core

uniform sampler2D uMainTexture;

uniform uvec2 uGridSize;
uniform float uEdgeWidth;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    vec2 pos = TexCoord * (uGridSize + uEdgeWidth) - uEdgeWidth * 0.5;
    pos = fract(pos);
    
    vec2 bottomLeft = step(uEdgeWidth * 0.5, pos);
    vec2 topRight = 1 - step(1.0 - uEdgeWidth * 0.5, pos);
    
    float isGrid = 1 - bottomLeft.x * bottomLeft.y * topRight.x * topRight.y;
    
    //float isGrid = min(pos.x, pos.y);
    
    FragColor = vec4(vec3(0.0), isGrid);
}