#include <glm/glm.hpp>
#include <iostream>
using namespace std;
using namespace glm;

void printMat4(mat4 m);

int main()
{
    vec3 s;
    vec3 u;
    vec3 f;
    vec3 e;
    s[0] = 1;
    s[1] = 2;
    s[2] = 3;
    u[0] = 4;
    u[1] = 5;
    u[2] = 6;
    f[0] = 7;
    f[1] = 8;
    f[2] = 9;
    e[0] = 10;
    e[1] = 11;
    e[2] = 12;

    mat4 result1(1);
    result1[0][0] = s.x;
    result1[1][0] = s.y;
    result1[2][0] = s.z;
    result1[0][1] = u.x;
    result1[1][1] = u.y;
    result1[2][1] = u.z;
    result1[0][2] = -f.x;
    result1[1][2] = -f.y;
    result1[2][2] = -f.z;
    result1[3][0] = e.x;
    result1[3][1] = e.y;
    result1[3][2] = e.z;
    printMat4(result1);
    // 经过测试得出结论 glm中矩阵的结构和二维数组一样
    mat4 result2(1);
    result2[0] = vec4(s, 0.0f);
    result2[1] = vec4(u, 0.0f);
    result2[2] = vec4(-f, 0.0f);
    result2 = transpose(result2);
    result2[3] = vec4(e, 1.0f);
    printMat4(result2);

    system("pause");
    return 0;
}

void printMat4(mat4 m)
{
    for (int i = 0; i < m.length(); i++)
    {
        cout << endl;
        for (int j = 0; j < m[i].length(); j++)
        {
            cout << m[i][j] << " \t";
        }
    }

    cout << endl;
}