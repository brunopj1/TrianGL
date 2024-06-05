#version 430 core

// Uniforms

uniform int uIsSpriteValid;
uniform sampler2D uSprite;
uniform mat4 uSpriteMatrix;
uniform uvec2 uSpriteResolution;

uniform vec4 uColor;

// Inputs

in vec2 texCoord;

// Outputs

out vec4 fragColor;

void main()
{
    if (uIsSpriteValid == 0) 
    {
        fragColor = uColor;
    }  
    else
    {
        vec2 uv = texCoord;
        
        // Prevent showing neighboring slices
        uv = min(uv, 1 - 1.0 / uSpriteResolution * 0.5);
        uv = max(uv, 1.0 / uSpriteResolution * 0.5);

        // Apply sprite matrix
        uv = (uSpriteMatrix * vec4(uv, 0.0, 1.0)).xy;
        
        fragColor = texture(uSprite, uv) * uColor;
    }
}