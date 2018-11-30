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

#define PIPE_ERRMSG_SIZE 512

enum state
{
    Accept,
    Complier_failed,
    Time_out,
    Time_exceed,
    Unexpect_context,
    Worry_ans,
    RunTime_error,
    Answer_error
};

void cpy_msg(char *dest, size_t size, const std::string &msg);

bool is_content_equal(int fd1, int fd2);

void execvp_vec(const std::vector<std::string> &parameters);

} // end of namespace guatoj

#endif //OJ_KERNEL_OJLIB_H
