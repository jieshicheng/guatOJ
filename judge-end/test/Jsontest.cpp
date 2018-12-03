#include "json/json.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    Json::Value root;
    Json::Reader read;
    ifstream ifs("../conf.json");
    read.parse(ifs, root);

    cout << root["cpp_file_path"].asString() << endl;
    cout << root["c_file_path"].asString() << endl;

    return 0;
}