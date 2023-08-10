#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat4 u_VP;
void main()
{
    TexCoords = aTexCoords;
    FragPos = aPos;
    Color = aColor;
    gl_Position = u_VP * u_Model * vec4(aPos, 1.0);
}