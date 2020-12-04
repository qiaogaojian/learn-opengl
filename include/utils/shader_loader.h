#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace glm;

class ShaderLoader
{
public:
	unsigned int ID;
	ShaderLoader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// 激活shader
	void use();

	// uniform工具函数
	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;
	void setVec2(const string& name, const vec2& value) const;
	void setVec2(const string& name, float x, float y) const;
	void setVec3(const string& name, const vec3& value) const;
	void setVec3(const string& name, float x, float y, float z) const;
	void setVec4(const string& name, const vec4& value) const;
	void setVec4(const string& name, float x, float y, float z, float w) const;
	void setMat2(const string& name, const mat2& mat) const;
	void setMat3(const string& name, const mat3& mat) const;
	void setMat4(const string& name, const mat4& mat) const;

    // concat string
    string concatString(char* s1,const char* s2);
    string subreplace(string resource_str, string sub_str, string new_str);

private:
	// 检查shader 编译 链接错误
	void checkCompileErrors(GLuint shader, string type);
};
#endif
