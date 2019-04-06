#include "pipe_manage.h"
#include "lib/oj_lib.h"

#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <vector>
#include <glog/logging.h>

namespace guatoj
{

PipeManage::PipeManage() : _read_fd(-1), _write_fd(-1)
{
    int pipe_fd[2] = {-1, -1};

    if (pipe(pipe_fd) != -1)
    {
        _read_fd = pipe_fd[0];
        _write_fd = pipe_fd[1];

        // set pipe noblock. when pipe is empty, read function will return -1
        int flags;
        flags = fcntl(_read_fd, F_GETFL);
        flags = flags | O_NONBLOCK;
        fcntl(_read_fd, F_SETFL, flags);

        flags = fcntl(_write_fd, F_GETFL);
        flags = flags | O_NONBLOCK;
        fcntl(_write_fd, F_SETFL, flags);

    }
    else
    {
        LOG(ERROR) << "pipe malloc error in construct";
        pipe_fd[0] = pipe_fd[1] = -1;
    }
}

PipeManage::~PipeManage()
{
    if (_read_fd != -1)
        close(_read_fd);
    if (_write_fd != -1)
        close(_write_fd);
}

} // end of namespace gautoj
