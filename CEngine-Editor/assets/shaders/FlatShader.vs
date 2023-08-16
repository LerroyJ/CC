#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout(location = 3) in float aTexIndex;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Model;

out vec4 v_Color;
out float v_TexIndex;
out vec2 v_TexCoord;

void main()
{
    v_TexCoord = aTexCoords;
    v_Color = aColor;
    v_TexIndex = aTexIndex;
    gl_Position = u_ViewProjectionMatrix  * vec4(aPos, 1.0);
}