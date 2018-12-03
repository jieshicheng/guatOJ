#include <iostream>
#include "http_server.hpp"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sstream>
#include "compiler.h"
#include "compare.h"
#include "OJlib.h"

using namespace std;

guatoj::state submit(const string &flag, const string &code_path, const string &input, const string &standard)
{
    guatoj::state ans = guatoj::Accept;
    guatoj::compiler *ptr;
    if (flag == "0")
        ptr = new guatoj::cpp_compiler("cjs", code_path, vector<string>(), "tmp/cpp/");
    else if (flag == "1")
        ptr = new guatoj::c_compiler("cjs", code_path, vector<string>(), "tmp/c/");
    else
        ptr = new guatoj::java_compiler("cjs", code_path, vector<string>(), "tmp/java/");

    string execuatable = ptr->do_compiler();
    cout << execuatable << endl;

    if (execuatable == "")
    {
        cout << ptr->get_compiler_errmsg() << endl;
        ans = guatoj::Complier_failed;
    }
    else
    {
        guatoj::Compare comp(input, standard, execuatable);
        ans = comp.run_compare();
    }
    guatoj::delete_file(execuatable);
    return ans;
}

int main(int argc, char *argv[])
{
    guatoj::state ans = submit(argv[1], argv[2], argv[3], argv[4]);
    cout << ans << endl;

    int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    server.set_http_handler<cinatra::POST>("/api/v1/source_code", [](cinatra::request& req, cinatra::response& res) {
        res.set_status_and_content(cinatra::status_type::ok, "hello world");
    });
    server.run();
    exit(0);
}