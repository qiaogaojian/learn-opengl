#version 330 core
layout(location = 0) in vec3 aPos;		// 位置变量的属性位置值为0
layout(location = 1) in vec3 aColor;	// 颜色变量的属性位置值为1
layout(location = 2) in vec2 aTexCoord; // 纹理变量的属性位置值为2
out vec3 outColor;						// 向fragment shader输出一个颜色
out vec2 texCoord;
uniform float offsetX;
void main()
{
	gl_Position = vec4(aPos,1.0);
	outColor = aColor;					// 将outColor设置为从顶点数据哪里得到的输入颜色
	texCoord = vec2(aTexCoord.x,aTexCoord.y);
};