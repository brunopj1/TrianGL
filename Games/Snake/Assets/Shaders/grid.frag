#version 430 core

uniform uvec2 uGridSize;

in vec2 texCoord;

out vec4 fragColor;

void main()
{
    vec2 gridIndex = min(vec2(texCoord * uGridSize), uGridSize - 1);
    uvec2 gridRemainder = uvec2(gridIndex) % 2;
    float tint = 0.6 + 0.05 * ((gridRemainder.x + gridRemainder.y) % 2);
    fragColor = vec4(vec3(tint), 1.0);
}