//
// Created by 程杰仕 on 2018/11/2.
//

#include <unistd.h>
#include <iostream>
#include "compiler.h"
#include "OJlib.h"
#include "single_pipe.h"
#include <errno.h>
#include <memory>
#include <sys/wait.h>
namespace guatoj
{

const std::string &compiler::get_file_path() const
{
    return _file_path;
}

void compiler::set_file_path(const std::string &file_path)
{
    _file_path = file_path;
}

const std::vector<std::string, std::allocator<std::string>> &compiler::get_parameters() const
{
    return _parameters;
}

void compiler::set_parameters(const std::vector<std::string, std::allocator<std::string>> &parameters)
{
    _parameters = parameters;
}

void compiler::clear_errmsg()
{
    _err_buff.clear();
}

const std::string &compiler::get_compiler_errmsg()
{
    return _err_buff;
}

/**
 * get compiler failed message from pipe
 * if pipe is -1 means that pipe is closed, catch exception and set errmsg
 */
void compiler::set_compiler_errmsg() noexcept
{
    int read_fd, write_fd;
    try
    {
        read_fd = _pipe_fd.get_read_descriptor();
    }
    catch (bad_pipe_exception &exp)
    {
        // ... log here
        _err_buff = "bad pipe exception in compiler::set_compiler_errmsg, can't get compiler error message, but the compiler is failed";
        return;
    }

    _err_buff = get_fd_content(read_fd);
}

std::string compiler::get_random_name()
{
    srand(time(nullptr));
    return std::to_string(rand());
}

const std::string &compiler::get_user_name() const
{
    return _user_name;
}

void compiler::set_user_name(const std::string &user_name)
{
    _user_name = user_name;
}

/**
 * _parameter[1] == source file path
 * _parameter[3] == destination file path
 *
 * @return the elf file path. if compiler failed return ""
 */
std::string cpp_compiler::do_compiler()
{
    clear_errmsg();

    pid_t pid;
    std::shared_ptr<char> buf_path(new char[MAX_PATHSIZE]);
    getcwd(buf_path.get(), MAX_PATHSIZE);
    std::string current_path(buf_path.get());
    append_divd(current_path);
    std::string execuate_file = current_path + _tmp_path + _user_name + get_random_name();

    if ((pid = fork()) == 0)
    {
        // child
        // exec g++ file
        // child process don't need readFd, it just write message to father process
        close(_pipe_fd.get_read_descriptor());
        // copy writeFd to stderr descriptor
        dup2(_pipe_fd.get_write_descriptor(), STDERR_FILENO);
        // close redundancy descriptor
        close(_pipe_fd.get_write_descriptor());

        _parameters[1] = _file_path;
        _parameters[3] = execuate_file;

        execvp_vec(_parameters);

        // if process run here. means error occur
        _exit(1);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            _err_buff = "error in do_compiler function: waitpid return -1";
            return std::string();
        }
        if (WEXITSTATUS(status) != 0)
        {
            set_compiler_errmsg();
            return std::string();
        }
        return execuate_file;
    }
}

std::string java_compiler::do_compiler()
{
    clear_errmsg();

    return "";
}

std::string c_compiler::do_compiler()
{
    clear_errmsg();

    pid_t pid;
    std::shared_ptr<char> buf_path(new char[MAX_PATHSIZE]);
    getcwd(buf_path.get(), MAX_PATHSIZE);
    std::string current_path(buf_path.get());
    append_divd(current_path);
    std::string execuate_file = current_path + _tmp_path + _user_name + get_random_name();
    if ((pid = fork()) == 0)
    {
        // child
        // exec g++ file
        // child process don't need readFd, it just write message to father process
        close(_pipe_fd.get_read_descriptor());
        // copy writeFd to stderr descriptor
        dup2(_pipe_fd.get_write_descriptor(), STDERR_FILENO);
        // close redundancy descriptor
        close(_pipe_fd.get_write_descriptor());

        _parameters[1] = _file_path;
        _parameters[3] = execuate_file;

        execvp_vec(_parameters);

        // if process run here. means error occur
        _exit(1);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            _err_buff = "error in do_compiler function: waitpid return -1";
            return std::string();
        }
        if (WEXITSTATUS(status) != 0)
        {
            set_compiler_errmsg();
            return std::string();
        }
        return execuate_file;
    }
}

} // end of namespace guatoj
