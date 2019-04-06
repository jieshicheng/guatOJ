//
// Created by 程杰仕 on 2018/11/2.
//

#include "compiler.h"
#include "lib/oj_lib.h"
#include "pipe_manage.h"

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <glog/logging.h>

namespace guatoj
{

Compiler::Compiler(const std::string &user_name, const std::string &file_path, const std::string tmp_path) :
            _user_name(user_name),
            _file_path(file_path),
            _err_buff(),
            _parameters(),
            _pipe_fd(),
            _tmp_path(tmp_path),
            _resource()
{

}

Compiler::~Compiler()
{
    
}

const std::string &Compiler::get_file_path() const
{
    return _file_path;
}

void Compiler::set_file_path(const std::string &file_path)
{
    _file_path = file_path;
}

const std::vector<std::string, std::allocator<std::string>> &Compiler::get_parameters() const
{
    return _parameters;
}

void Compiler::set_parameters(const std::vector<std::string, std::allocator<std::string>> &parameters)
{
    _parameters = parameters;
}

void Compiler::ClearErrmsg()
{
    _err_buff.clear();
}

const std::string &Compiler::GetCompilerErrmsg()
{
    return _err_buff;
}

bool Compiler::DoFork(const std::string &execute_file)
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        // child
        // exec g++ file
        // child process don't need readFd, it just write message to father process
        close(_pipe_fd.get_read_fd());
        // copy writeFd to stderr descriptor
        dup2(_pipe_fd.get_write_fd(), STDERR_FILENO);
        // close redundancy descriptor
        close(_pipe_fd.get_write_fd());

        _parameters[1] = _file_path;
        _parameters[3] = execute_file;

        /*
        _resource.set_CORE_max(0);
        _resource.set_CPU_max(COMPILER_TIME);
        */

        ExecvpVec(_parameters);

        // if process run here. means error occur
        LOG(FATAL) << "process should't be here";
        _exit(1);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            _err_buff = "error in do_compiler function: waitpid return -1";
            LOG(FATAL) << _err_buff;
            return false;
        }
        if (WEXITSTATUS(status) != 0)
        {
            SetCompilerErrmsg();
            return false;
        }
        return true;
    }
}

/**
 * get compiler failed message from pipe
 * if pipe is -1 means that pipe is closed, catch exception and set errmsg
 */
void Compiler::SetCompilerErrmsg() noexcept
{
    int read_fd = _pipe_fd.get_read_fd();
    _err_buff = GetFdContent(read_fd);
}

std::string Compiler::GetRandomName()
{
    srand(time(nullptr));
    return std::to_string(rand());
}

const std::string &Compiler::get_user_name() const
{
    return _user_name;
}

void Compiler::set_user_name(const std::string &user_name)
{
    _user_name = user_name;
}

/**
 * cpp compiler.
 * _parameter[1] == source file path
 * _parameter[3] == destination file path
 *
 * @return the elf file path. if compiler failed return ""
 */
CppCompiler::CppCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        Compiler(user_name, file_path, tmp_path)
{
    _parameters.push_back("g++");
    _parameters.push_back(""); //source file path
    _parameters.push_back("-o");
    _parameters.push_back(""); // destination file path
    _parameters.push_back("-std=c++0x");
    for (const auto &str : parameters)
        _parameters.push_back(str);
}

std::string CppCompiler::DoCompiler()
{
    ClearErrmsg();

    std::shared_ptr<char> buf_path(new char[MAX_PATHSIZE]);
    getcwd(buf_path.get(), MAX_PATHSIZE);
    std::string current_path(buf_path.get());
    AppendDivd(current_path);
    std::string execuate_file = current_path + _tmp_path + _user_name + GetRandomName();

    if (DoFork(execuate_file) == true)
        return execuate_file;
    else
        return "";

}

/**
 * java compiler
 * _parameters[1] = source file path
 * _parameters[3] = destination file path
 * 
 * @return the elf file path. if compiler failed return ""
 */
JavaCompiler::JavaCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        Compiler(user_name, file_path, tmp_path)
{
    _parameters.push_back("javac");
    _parameters.push_back("");
    _parameters.push_back("-d");
    _parameters.push_back("");
    for (const auto &str : parameters)
        _parameters.push_back(str);
}

std::string JavaCompiler::DoCompiler()
{
    ClearErrmsg();

    std::shared_ptr<char> buf_path(new char[MAX_PATHSIZE]);
    getcwd(buf_path.get(), MAX_PATHSIZE);
    std::string current_path(buf_path.get());
    AppendDivd(current_path);
    current_path += _tmp_path;
    AppendDivd(current_path);
    if (DoFork(current_path) == true)
        return current_path + _file_path.substr(_file_path.find_last_of('/') + 1, 
                _file_path.find_last_of('.') - _file_path.find_last_of('/') - 1) + ".class";
    else
        return "";
}

/**
 * c compiler
 * _parameters[1] = source file path
 * _parameters[3] = destination file path
 * 
 * @return the elf file path. if compiler failed return ""
 */
CCompiler::CCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        Compiler(user_name, file_path, tmp_path)
{
    _parameters.push_back("gcc");
    _parameters.push_back("");
    _parameters.push_back("-o");
    _parameters.push_back("");
    _parameters.push_back("-std=c11");
    for (const auto &str : parameters)
        _parameters.push_back(str);
}

std::string CCompiler::DoCompiler()
{
    ClearErrmsg();

    std::shared_ptr<char> buf_path(new char[MAX_PATHSIZE]);
    getcwd(buf_path.get(), MAX_PATHSIZE);
    std::string current_path(buf_path.get());
    AppendDivd(current_path);
    std::string execuate_file = current_path + _tmp_path + _user_name + GetRandomName();
    if (DoFork(execuate_file) == true)
        return execuate_file;
    else
        return "";
}

} // end of namespace guatoj