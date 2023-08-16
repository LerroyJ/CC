#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Model;
out vec2 v_TexCoords;

void main()
{
    v_TexCoords = aTexCoords;
    gl_Position = u_ViewProjectionMatrix  * u_Model * vec4(aPos, 1.0);
}