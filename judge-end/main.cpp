#include <iostream>
#include "http_server.hpp"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sstream>
#include "compiler.h"
#include "compare.h"

using namespace std;

guatoj::state submit(const string &code_path, const string &input, const string &standard)
{
    guatoj::state ans = guatoj::Accept;

    guatoj::cpp_compiler item("cjs", code_path, vector<string>());

    string execuatable = item.do_compiler();
    cout << execuatable << endl;


    if (execuatable == "")
    {
        cout << item.get_compiler_errmsg() << endl;
        ans = guatoj::Complier_failed;
    }
    else
    {
        guatoj::Compare comp(input, standard, execuatable);
        ans = comp.run_compare();
    }
    return ans;
}

int main(int argc, char *argv[])
{
    // para 1：file name of itself
    // para 2：file path of ready to complier
    // para 3: input test data direct
    // para 4: standard output test data direct
    if (argc != 4)
    {
        cout << "parameter error.it should equal 3" << endl;
        exit(1);
    }

    guatoj::state ans = submit(string(argv[1]), string(argv[2]), string(argv[3]));
    if (ans == guatoj::Accept)
    {
        cout << "right" << endl;
    }
    else if (ans == guatoj::Worry_ans)
    {
        cout << "worry" << endl;
    }
    else if (ans == guatoj::Complier_failed)
    {

    }

    int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    server.set_http_handler<cinatra::POST>("/api/v1/", [](cinatra::request& req, cinatra::response& res) {
        res.set_status_and_content(cinatra::status_type::ok, "hello world");
    });
    server.run();
    exit(0);
}