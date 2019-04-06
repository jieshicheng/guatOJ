//
// Created by 程杰仕 on 2018/6/4.
//

#ifndef GUATOJ_JUDGE_LIB_OJ_LIB_H_
#define GUATOJ_JUDGE_LIB_OJ_LIB_H_

#include <cstddef>
#include <string>
#include <vector>

namespace guatoj
{
    
#define READ_BYTES 512
#define PIPE_ERRMSG_SIZE 512
#define MAX_PATHSIZE 512
#define COMPILER_TIME 8

enum SubmitState
{
    Accept, // code work correctly
    CompilerFailed, // compiler error
    SystemError, // system unknow error
    TimeOut, // exceed the time that subject stipulated
    WorryAns, // code work error
    RunTimeError, // in the run time, your code make mistake
    AnswerError // this means the question relevant documents error
};

void CpyMsg(char *dest, size_t size, const std::string &msg);

bool IsContentEqual(int fd1, int fd2);

void ExecvpVec(const std::vector<std::string> &parameters);

std::string GetFdContent(int fd);

void AppendDivd(std::string &str);

bool DeleteFile(const std::string &file_path);

} // end of namespace guatoj

#endif // GUATOJ_JUDGE_LIB_OJ_LIB_H_
