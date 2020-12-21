#ifndef TOOLS_H
#define TOOLS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace glm;

string concatString(char *s1, const char *s2);
string subreplace(string resource_str, string sub_str, string new_str);

// concat string
string concatString(char *s1, const char *s2)
{
    string temp = subreplace(string(s1), "\\", "/") + string(s2) + "\0";
    return temp;
}

string subreplace(string resource_str, string sub_str, string new_str)
{
    string::size_type pos = 0;
    while ((pos = resource_str.find(sub_str)) != string::npos) //替换所有指定子串
    {
        resource_str.replace(pos, sub_str.length(), new_str);
    }
    return resource_str;
}
#endif