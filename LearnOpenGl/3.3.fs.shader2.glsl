#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 outColor;

uniform sampler2D textureBox;

void main()
{
	FragColor = texture(textureBox,texCoord)*vec4(outColor,1.0f);
};