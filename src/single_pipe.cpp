//
// Created by 程杰仕 on 2018/6/4.
//

#include <zconf.h>
#include <fcntl.h>
#include <iostream>
#include "single_pipe.h"
#include "lib/OJlib.h"

namespace guatoj
{

single_pipe::single_pipe() : _read_descriptor(-1), _write_descriptor(-1)
{
    int pipe_fd[2] = {-1, -1};

    if (pipe(pipe_fd) != -1)
    {
        _read_descriptor = pipe_fd[0];
        _write_descriptor = pipe_fd[1];

        // set pipe noblock. when pipe is empty, read function will return -1
        int flags;
        flags = fcntl(_read_descriptor, F_GETFL);
        flags = flags | O_NONBLOCK;
        fcntl(_read_descriptor, F_SETFL, flags);

        flags = fcntl(_write_descriptor, F_GETFL);
        flags = flags | O_NONBLOCK;
        fcntl(_write_descriptor, F_SETFL, flags);

    }
    else
    {
        printf("pipe malloc error in construct\n");
        pipe_fd[0] = pipe_fd[1] = -1;
    }

}

single_pipe::~single_pipe()
{
    close(_read_descriptor);
    close(_write_descriptor);

}

} // end of namespace gautoj