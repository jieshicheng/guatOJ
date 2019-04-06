//
// Created by jieshicheng on 2018/6/4.
// 

#ifndef GUATOJ_JUDGEEND_SRC_SINGLE_PIPE_H_
#define GUATOJ_JUDGEEND_SRC_SINGLE_PIPE_H_

#include <exception>
#include <glog/logging.h>

namespace guatoj
{

class BadPipeException : public std::exception
{
public:
    virtual const char *what()
    {
        return "pipe create failed";
    }
};

/**
 * pipe manage.RAII
 */
class PipeManage
{

public:
    PipeManage();

    ~PipeManage();

    int get_read_fd() noexcept(false)
    {
        return _read_fd;
    }

    int get_write_fd() noexcept(false)
    {
        return _write_fd;
    }

private:
    int _read_fd;
    int _write_fd;
};

} // end of namespace guatoj

#endif //GUATOJ_JUDGEEND_SRC_SINGLE_PIPE_H_
