#version 330 core
out vec4 FragColor;

in vec2 v_TexCoords;

void main(){
	FragColor = vec4(v_TexCoords, 0, 1);
}