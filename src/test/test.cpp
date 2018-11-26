//
// Created by 程杰仕 on 2018/11/23.
//

#include <iostream>
#include <unistd.h>
using namespace std;

class Obj
{
public:
    Obj()
    {
        cout << "construct" << endl;
    }
    ~Obj()
    {
        cout << "destory" << endl;
    }
};


int main()
{
    char *str = new char[20];
    memcpy(str, "chengjieshi", 12);
    cout << str << endl;
    string ans = "i am ";
    ans = ans + str;
    cout << ans << endl;
    memcpy(str, "hubing", 7);
    cout << ans << endl;

    return 0;
}