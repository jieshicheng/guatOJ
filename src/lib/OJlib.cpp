//
// Created by 程杰仕 on 2018/6/4.
//

#include <zconf.h>
#include <iostream>
#include "OJlib.h"
#include <vector>

namespace guatoj
{

/**
 * copy message from string to char buffer
 *
 */
void cpy_msg(char *dest, size_t size, const std::string &msg)
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
 * first para meaning the standard answer
 * second para meaning the answer that ready for test
 * Tips:
 *      buffer is limit by 256 bytes,it should be improve by getting the size of the
 *      standardDesc and using it to limit the buffer
 */
bool is_content_equal(int fd1, int fd2)
{
    char bufferA[256], bufferB[256];
    // keep the already read bytes and status of read
    ssize_t stat;
    // the size of standard answer. it be limited by 256
    ssize_t output_data_length = 0;
    while ((stat = read(fd1, bufferA, 256)) != 0)
    {
        if (stat == -1)
        {
            if (errno == EAGAIN)
            {
                // read empty descriptor.
                break;
            }
            else
            {
                // should add error process
                exit(1);
            }
        }
        output_data_length += stat;
    }
    bufferA[output_data_length] = '\0';
    std::cout << bufferA << std::endl;
    while ((stat = read(fd2, bufferB, output_data_length)) != 0)
    {
        if (stat == -1)
        {
            if (errno == EAGAIN)
            {
                break;
            }
            else
            {
                // should add error process
                exit(1);
            }
        }
    }
    bufferB[output_data_length] = '\0';
    std::cout << bufferB << std::endl;
    stat = 0;
    while (stat < output_data_length)
    {
        if (bufferA[stat] != bufferB[stat])
            return false;
        ++stat;
    }
    return true;
}

void execvp_vec(const std::vector<std::string> &parameters)
{
    char *arg_vec[parameters.size() + 1];
    for (int i = 0; i != parameters.size(); ++i)
        arg_vec[i] = const_cast<char *>(parameters[i].c_str());
    arg_vec[parameters.size()] = nullptr;
    execvp(arg_vec[0], (arg_vec));
}


} // end of namespace guatoj