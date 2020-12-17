#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 resColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat; // 法线矩阵 用来消除不同比例缩放对法线方向的影响

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 Normal = normalMat * aNormal;
    vec3 FragPos = vec3(model * vec4(aPos,1.0));

    // 环境光
    float ambientStrength=.1;
    vec3 ambient=ambientStrength*lightColor;

    // 漫反射
    vec3 normalDir=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(normalDir,lightDir),0);
    vec3 diffuse=diff*lightColor;

    // 镜面反射
    float specularStrength=.5;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,normalDir);// 反射函数第一个参数是入射光方向 第二个参数是法线方向
    float spec=pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular=specularStrength*spec*lightColor;

    resColor=(ambient+diffuse+specular)*objectColor;
}