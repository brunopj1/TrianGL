#version 430 core

uniform float uBorderRadius;
uniform int uIsSpriteValid;
uniform sampler2D uSprite;
uniform mat4 uSpriteMatrix;
uniform uvec2 uSpriteResolution;

in vec2 texCoord;
in vec4 color;
in float remainingDuration;

out vec4 fragColor;

void main()
{
    if (remainingDuration <= 0.0) discard;

    float alpha = 1.0;
    float borderRadius = clamp(uBorderRadius, 0.0, 0.5);
    if (borderRadius != 0.0)
    {
        vec2 dist = abs(texCoord - vec2(0.5)) - (vec2(0.5) - borderRadius);
        float d = length(max(dist, 0.0)) - borderRadius;
        alpha = 1.0 - step(0.0, d);
    }
    
    float fade = clamp(remainingDuration, 0.0, 1.0);
    
    if (uIsSpriteValid == 0) 
    {
        fragColor = vec4(color.xyz, 1.0);
    }
    else
    {
        vec2 uv = texCoord;

         // Prevent showing neighboring slices
         uv = min(uv, 1 - 1.0 / uSpriteResolution * 0.5);
         uv = max(uv, 1.0 / uSpriteResolution * 0.5);
    
         // Apply sprite matrix
         uv = (uSpriteMatrix * vec4(uv, 0.0, 1.0)).xy;
    
         fragColor = texture(uSprite, uv);
    }

    fragColor.a *= alpha * fade;
}