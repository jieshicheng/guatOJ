//
// Created by 程杰仕 on 2018/6/4.
//

#ifndef OJ_KERNEL_SINGLEPIPE_H
#define OJ_KERNEL_SINGLEPIPE_H


#include <exception>

namespace guatoj
{

class bad_pipe_exception : public std::exception
{
public:
    virtual const char *what()
    {
        return "pipe create failed";
    }
};

class single_pipe
{

public:
    single_pipe();

    ~single_pipe();

    int get_read_descriptor() noexcept(false)
    {
        if (_read_descriptor == -1)
            throw bad_pipe_exception();
        return _read_descriptor;
    }

    int get_write_descriptor() noexcept(false)
    {
        if (_write_descriptor == -1)
            throw bad_pipe_exception();
        return _write_descriptor;
    }

private:
    int _read_descriptor;
    int _write_descriptor;

};

} // end of namespace guatoj

#endif //OJ_KERNEL_SINGLEPIPE_H
