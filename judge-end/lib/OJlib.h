//
// Created by 程杰仕 on 2018/6/4.
//

#ifndef OJ_KERNEL_OJLIB_H
#define OJ_KERNEL_OJLIB_H

#include <cstddef>
#include <string>
#include <vector>

namespace guatoj
{
#define READ_BYTES 512
#define PIPE_ERRMSG_SIZE 512
#define MAX_PATHSIZE 512

enum state
{
    Accept, // code work correctly
    Complier_failed, // compiler error
    Time_out, // exceed the time that subject stipulated
    Worry_ans, // code work error
    RunTime_error, // in the run time, your code make mistake
    Answer_error // this means the question relevant documents error
};

void cpy_msg(char *dest, size_t size, const std::string &msg);

bool is_content_equal(int fd1, int fd2);

void execvp_vec(const std::vector<std::string> &parameters);

std::string get_fd_content(int fd);

void append_divd(std::string &str);

bool delete_file(const std::string &file_path);

} // end of namespace guatoj

#endif //OJ_KERNEL_OJLIB_H
