#version 430 core

in vec2 texCoord;
in vec4 color;
in float life;

out vec4 fragColor;

void main()
{
    if (life <= 0.0) discard;
    
    float dist = distance(texCoord, vec2(0.5, 0.5));
    float alpha = 1 - step(0.5, dist);
    
    float fade = clamp(life, 0.0, 1.0);
    
    fragColor = vec4(color.xyz, alpha * fade);
}