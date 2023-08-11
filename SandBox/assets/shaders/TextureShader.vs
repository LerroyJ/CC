#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

out vec2 TexCoords;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Model;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = u_ViewProjectionMatrix * u_Model * vec4(aPos, 1.0);
}