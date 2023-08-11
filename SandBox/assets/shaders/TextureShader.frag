#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform float u_xScale;
uniform float u_yScale;
void main()
{
    vec2 scale = vec2(u_xScale, u_yScale);
    vec4 color = texture(u_Texture, TexCoords * scale) * u_Color;
    FragColor = color;
}