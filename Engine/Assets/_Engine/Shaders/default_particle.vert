#version 430 core

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec2 aQuadTexCoord;
layout (location = 2) in vec2 aParticlePosition;
layout (location = 3) in vec4 aParticleColor;
layout (location = 4) in float aParticleScale;
layout (location = 5) in float aParticleRotation;
layout (location = 6) in float aParticleRemainingDuration;

out vec2 texCoord;
out vec4 color;
out float remainingDuration;

void main()
{
    mat4 particleTranslationMatrix = mat4(1.0);
    particleTranslationMatrix[3][0] = aParticlePosition.x;
    particleTranslationMatrix[3][1] = aParticlePosition.y;

    mat4 particleScaleMatrix = mat4(1.0);
    particleScaleMatrix[0][0] = aParticleScale;
    particleScaleMatrix[1][1] = aParticleScale;

    float cosTheta = cos(aParticleRotation);
    float sinTheta = sin(aParticleRotation);
    mat4 particleRotationMatrix = mat4(1.0);
    particleRotationMatrix[0][0] = cosTheta;
    particleRotationMatrix[0][1] = -sinTheta;
    particleRotationMatrix[1][0] = sinTheta;
    particleRotationMatrix[1][1] = cosTheta;

    mat4 particleTransformMatrix = particleTranslationMatrix * particleRotationMatrix * particleScaleMatrix;
    mat4 pvmMatrix = uProjectionMatrix * uViewMatrix * particleTransformMatrix;
    
    gl_Position = pvmMatrix * vec4(aQuadPos, 0.0, 1.0);
    
    texCoord = aQuadTexCoord;
    color = aParticleColor;
    remainingDuration = aParticleRemainingDuration;
}