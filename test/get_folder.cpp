#include <direct.h>
#include <iostream>
using namespace std;

int main()
{
    cout << string(getcwd(NULL, 0)) << endl;

    system("pause");
    return 0;
}