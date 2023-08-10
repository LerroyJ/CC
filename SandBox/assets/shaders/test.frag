#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Color;

uniform vec3 u_Color;
uniform sampler2D u_Albedo;
uniform float u_Intense;

void main()
{
    vec4 color = texture(u_Albedo, TexCoords);
    FragColor = color;
}