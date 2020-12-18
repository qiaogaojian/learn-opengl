#version 330 core
struct Material {
    sampler2D diffuse;   // 移除了环境光材质颜色向量，因为环境光颜色在几乎所有情况下都等于漫反射颜色，不需要将它们分开储存
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3  position;  // 聚光位置
    vec3  direction; // 聚光方向
    float cutOff;    // 切光角

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 衰减系数
    float constant;  // 常数项
    float linear;    // 一次项
    float quadratic; // 二次项
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 lightDir = normalize(vec3(light.position) - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    float len = length(vec3(light.position) - FragPos);
    float attenuation  = 1 / (light.constant + light.linear * len + light.quadratic * len * len ); // 衰减
    if (theta > light.cutOff) { // 聚光灯
         // 环境光
         vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
         // 聚光灯
         vec3 spot = vec3(texture(material.diffuse, TexCoord)) * attenuation;
         // 镜面反射
         vec3 viewDir=normalize(viewPos-FragPos);
         vec3 reflectDir=reflect(-lightDir,normalize(Normal));// 反射函数第一个参数是入射光方向 第二个参数是法线方向
         float spec=pow(max(dot(viewDir,reflectDir),0),shininess);
         vec3 specular=light.specular * spec * vec3(texture(material.specular,TexCoord)) * attenuation;
         FragColor = vec4(ambient + spot + specular, 1.);
    } else {                   // 只有环境光
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
        FragColor = vec4(ambient ,1.);
    }
}