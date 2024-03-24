#version 430 core

// Uniforms

uniform int uIsTextureValid;

uniform sampler2D uTexture;
uniform mat4 uTextureMatrix;
uniform uvec2 uTextureResolution;

uniform vec4 uColor;

// Inputs

in vec2 texCoord;

// Outputs

out vec4 fragColor;

void main()
{
    if (uIsTextureValid == 0) 
    {
        fragColor = uColor;
    }  
    else
    {
        vec2 uv = texCoord;
        
        // Prevent showing neighboring slices
        uv = min(uv, 1 - 1.0 / uTextureResolution * 0.5);
        uv = max(uv, 1.0 / uTextureResolution * 0.5);

        // Apply texture matrix
        uv = (uTextureMatrix * vec4(uv, 0.0, 1.0)).xy;
        
        fragColor = texture(uTexture, uv) * uColor;
    }
}