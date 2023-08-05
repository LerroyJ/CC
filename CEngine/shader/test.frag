#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;

void main()
{
    
    FragColor = vec4(FragPos * 0.5 + 0.5, 1.0);
}