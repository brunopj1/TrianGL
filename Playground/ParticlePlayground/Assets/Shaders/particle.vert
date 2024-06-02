#version 430 core

uniform mat4 uPVMMatrix;

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec2 aQuadTexCoord;
layout (location = 2) in vec2 aParticlePosition;
layout (location = 3) in vec2 aParticleVelocity;
layout (location = 4) in vec4 aParticleColor;
layout (location = 5) in float aParticleLife;

out vec2 texCoord;
out vec4 color;
out float life;

void main()
{
    gl_Position = uPVMMatrix * vec4(aQuadPos * 0.2 + aParticlePosition, 0.0, 1.0);
    
    texCoord = aQuadTexCoord;
    color = aParticleColor;
    life = aParticleLife;
}