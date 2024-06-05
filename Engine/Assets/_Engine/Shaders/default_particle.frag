#version 430 core

in vec2 texCoord;
in vec4 color;
in float remainingDuration;

out vec4 fragColor;

void main()
{
    if (remainingDuration <= 0.0) discard;

    float fade = clamp(remainingDuration, 0.0, 1.0);

    fragColor = vec4(color.xyz, fade);
}