//
// Created by 程杰仕 on 2018/6/4.
//

//#include <zconf.h>

#include "lib/oj_lib.h"

#include <unistd.h>

#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include <glog/logging.h>


namespace guatoj
{

/**
 * copy message from string msg to char * dest.
 * caller should promise that dest's space greater than or equal size.
 */
void CpyMsg(char *dest, size_t size, const std::string &msg)
{
    size_t length;
    if (msg.size() < size)
    {
        length = msg.size();
    }
    else
    {
        length = size;
    }
    memcpy(dest, msg.c_str(), length);
    dest[length] = '\0';
}

/**
 * using string to stores the content of fd.
 * every time read READ_BYTES bytes from fd, and store in string.
 * untill get the -1 of EOL
 */
std::string GetFdContent(int fd)
{
    std::shared_ptr<char> sp(new char[READ_BYTES]);
    std::string buffer;

    size_t already_read = 0;
    int readed;
    while ((readed = read(fd, sp.get(), READ_BYTES)) != 0)
    {
        if (readed == -1)
        {
            if (errno == EAGAIN)
            {
                break;
            }
            else
            {
                //fetal error
            }
        }
        sp.get()[readed] = '\0';
        already_read += readed;
        buffer += sp.get();
    }

    return buffer;
}

/**
 * check the two file descriptor's content whether same.
 *
 */
bool IsContentEqual(int fd1, int fd2)
{
    std::string text1 = GetFdContent(fd1);
    std::string text2 = GetFdContent(fd2);
    LOG(INFO) << text1 << text2;
    if (text1.length() != text2.length() || text1 != text2)
        return false;
    else
        return true;
}

/**
 * exec a new procedure, it recive vector<string> as parameters
 *  and transfer it to char *[] to execvp function.
 */
void ExecvpVec(const std::vector<std::string> &parameters)
{
    char *arg_vec[parameters.size() + 1];
    for (int i = 0; i != parameters.size(); ++i)
        arg_vec[i] = const_cast<char *>(parameters[i].c_str());
    arg_vec[parameters.size()] = nullptr;
    execvp(arg_vec[0], (arg_vec));
}

/**
 * This function checks whether the str ends with /, if not then append to
 */
void AppendDivd(std::string &str)
{
    if (str == "")
        return;
    if (*(str.end() - 1) != '/')
        str = str + "/";
}

bool DeleteFile(const std::string &file_path)
{
    if (unlink(file_path.c_str()) == 0)
        return true;
    else 
        return false;
}

} // end of namespace guatoj
