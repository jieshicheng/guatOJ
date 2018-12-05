//
// Created by 程杰仕 on 2018/11/2.
//

#ifndef GUATOJ_COMPILER_H
#define GUATOJ_COMPILER_H

#include <string>
#include <vector>
#include <exception>
#include "single_pipe.h"

namespace guatoj
{

class pipe_read_exception : public std::exception
{
public:
    virtual const char *what()
    {
        return "read pipe occurred error";
    }
};


/**
 *  compiler base class
 *  abstract function do_compiler() is an interface
 */
class compiler
{
public:
    compiler(const std::string &user_name, const std::string &file_path, const std::string tmp_path) :
            _user_name(user_name),
            _file_path(file_path),
            _err_buff(),
            _parameters(),
            _pipe_fd(),
            _tmp_path(tmp_path)
    {

    }

    virtual ~compiler()
    {
    }

    const std::string &get_compiler_errmsg();

    // compiler interface
    virtual std::string do_compiler() = 0;

    // generate code for get and set
    const std::string &get_file_path() const;
    void set_file_path(const std::string &file_path);
    const std::vector<std::string, std::allocator<std::string>> &get_parameters() const;
    void set_parameters(const std::vector<std::string, std::allocator<std::string>> &parameters);
    const std::string &get_user_name() const;
    void set_user_name(const std::string &user_name);


protected:
    void clear_errmsg();
    void set_compiler_errmsg() noexcept;
    std::string get_random_name();
    bool do_fork(const std::string &execute_file);

    std::string _user_name;
    std::string _file_path;
    std::string _err_buff;
    std::vector<std::string> _parameters;
    guatoj::single_pipe _pipe_fd;
    std::string _tmp_path;

};


class cpp_compiler : public compiler
{
public:
    virtual std::string do_compiler();

    cpp_compiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        compiler(user_name, file_path, tmp_path)
    {
        _parameters.push_back("g++");
        _parameters.push_back(""); //source file path
        _parameters.push_back("-o");
        _parameters.push_back(""); // destination file path
        _parameters.push_back("-std=c++0x");
        for (const auto &str : parameters)
            _parameters.push_back(str);
    }
};

class c_compiler : public compiler
{
public:
    virtual std::string do_compiler();

    c_compiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        compiler(user_name, file_path, tmp_path)
    {
        _parameters.push_back("gcc");
        _parameters.push_back("");
        _parameters.push_back("-o");
        _parameters.push_back("");
        _parameters.push_back("-std=c11");
        for (const auto &str : parameters)
            _parameters.push_back(str);
    }
};

class java_compiler : public compiler
{
public:
    virtual std::string do_compiler();

    java_compiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path) :
        compiler(user_name, file_path, tmp_path)
    {
        _parameters.push_back("javac");
        _parameters.push_back("");
        _parameters.push_back("-d");
        _parameters.push_back("");
        for (const auto &str : parameters)
            _parameters.push_back(str);
    }
};

} // end of namespace guatoj

#endif //GUATOJ_COMPILER_H
