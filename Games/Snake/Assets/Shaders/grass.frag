#version 430 core

uniform float uSeed;
uniform uvec2 uGridSize;
uniform sampler2D uSpriteSheet;
uniform mat4 uSpriteGrassNormalMatrix;
uniform mat4 uSpriteGrassTallMatrix;
uniform mat4 uSpriteGrassFlowersMatrix;
uniform mat4 uSpriteGrassRocksMatrix;

in vec2 texCoord;

out vec4 fragColor;

int randInt(float seed, int minValue, int maxValue) {
    float hash = fract(sin(seed) * 43758.5453123);
    return minValue + int(floor(hash * float(maxValue - minValue + 1)));
}

void main()
{
    vec2 gridScaled = texCoord * uGridSize;
    ivec2 gridIndex = ivec2(floor(gridScaled));
    int gridRemainder = (gridIndex.x + gridIndex.y) % 2;
    
    float seed = uSeed + gridIndex.y * int(uGridSize.x) + gridIndex.x;
    int randomValue = randInt(seed, 0, 10);
    
    mat4 uvMatrix;
    if (randomValue <= 7) uvMatrix = uSpriteGrassNormalMatrix;
    else if (randomValue == 8) uvMatrix = uSpriteGrassTallMatrix;
    else if (randomValue == 9) uvMatrix = uSpriteGrassFlowersMatrix;
    else /* randomValue == 10 */ uvMatrix = uSpriteGrassRocksMatrix;

    vec2 uv = fract(gridScaled);
    uv = (uvMatrix * vec4(uv, 0.0, 1.0)).xy;
    
    fragColor = texture(uSpriteSheet, uv);
    
    if (gridRemainder == 1) fragColor *= 0.90;
}