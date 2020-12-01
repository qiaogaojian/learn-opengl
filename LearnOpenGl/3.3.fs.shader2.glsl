#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 outColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float factor;

void main()
{
	FragColor = mix(texture(texture1,texCoord),texture(texture2,texCoord),factor);
};