#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Model;

out vec4 Color;

void main()
{
    Color = aColor;
    gl_Position = u_ViewProjectionMatrix  * vec4(aPos, 1.0);
}