#include "compiler.h"
#include "http_server.hpp"
#include "compare.h"
#include "lib/oj_lib.h"
#include "json/json.h"

#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sstream>
#include <string>
#include <fstream>
#include <glog/logging.h>
#include <iostream>

using namespace std;

guatoj::SubmitState Submit(const string &flag, const string &code_path, const string &input, const string &standard)
{
    guatoj::SubmitState ans = guatoj::Accept;
    guatoj::Compiler *ptr;
    if (flag == "0")
        ptr = new guatoj::CppCompiler("cjs", code_path, vector<string>(), "tmp/cpp/");
    else if (flag == "1")
        ptr = new guatoj::CCompiler("cjs", code_path, vector<string>(), "tmp/c/");
    else if (flag == "2")
        ptr = new guatoj::JavaCompiler("cjs", code_path, vector<string>(), "tmp/java/");

    string execuatable = ptr->DoCompiler();
    cout << execuatable << endl;
    if (execuatable == "")
    {
        cout << ptr->GetCompilerErrmsg() << endl;
        ans = guatoj::CompilerFailed;
    }
    else
    {
        guatoj::Question qes(input, standard, 1024 * 1024 * 1024, 10);
        guatoj::Compare comp(execuatable, qes);
        if (flag == "2")
            ans = comp.RunJavaCompare();
        else
            ans = comp.RunCstyleCompare();
    }
    guatoj::DeleteFile(execuatable);
    return ans;
}

int main(int argc, char *argv[])
{
    /*
    guatoj::SubmitState ans = Submit(argv[1], argv[2], argv[3], argv[4]);
    cout << ans << endl;
    */

    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "./log/INFO_");
    google::SetLogDestination(google::ERROR, "./log/ERROR_");
    google::SetLogDestination(google::FATAL, "./log/FATAL_");
    FLAGS_logbufsecs = 10; 

    Json::Value conf;
    Json::Reader read;
    ifstream ifs("conf.json");
    read.parse(ifs, conf);

    for (int i = 0; i != 1000; ++i)
        LOG(INFO) << i; 

    for (int i = 0; i != 1000; ++i)
        LOG(INFO) << i; 
    int a = 10;

    int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");

    server.set_http_handler<cinatra::GET>("/", [](cinatra::request &req, cinatra::response &res) {
        res.set_status_and_content(cinatra::status_type::ok, "index.php");
    });

    server.run();

    google::ShutdownGoogleLogging();
    return 0;
}