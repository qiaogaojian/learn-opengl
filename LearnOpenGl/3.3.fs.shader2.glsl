#version 330 core
out vec4 FragColor;
uniform float uniColor2;
void main()
{
	FragColor = vec4(0.0f,1.0f,uniColor2,1.0f);
};