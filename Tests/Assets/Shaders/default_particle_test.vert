#version 430 core

uniform int uSize;

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec2 aQuadTexCoord;
layout (location = 2) in vec2 aParticlePosition;
layout (location = 3) in vec4 aParticleColor;
layout (location = 4) in float aParticleScale;
layout (location = 5) in float aParticleRotation;
layout (location = 6) in float aParticleRemainingDuration;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos * uSize, 0.0, 1.0);
    texCoord = aTexCoord;
}