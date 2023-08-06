#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Color;

void main()
{
    
    FragColor = vec4(FragPos * 0.5 + 0.5, 1.0);
    FragColor = vec4(Color, 1.0);
}