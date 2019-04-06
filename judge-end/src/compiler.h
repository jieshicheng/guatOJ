//
// Created by 程杰仕 on 2018/11/2.
//

#ifndef GUATOJ_JUDGEEND_SRC_COMPILER_H_
#define GUATOJ_JUDGEEND_SRC_COMPILER_H_

#include "pipe_manage.h"
#include "resource_limit.h"

#include <string>
#include <vector>
#include <exception>

namespace guatoj
{

class PipeReadException : public std::exception
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
class Compiler
{
public:
    Compiler(const std::string &user_name, const std::string &file_path, const std::string tmp_path);

    virtual ~Compiler();

    const std::string &GetCompilerErrmsg();

    // compiler interface
    virtual std::string DoCompiler() = 0;

    // generate code for get and set
    const std::string &get_file_path() const;
    void set_file_path(const std::string &file_path);

    const std::vector<std::string, std::allocator<std::string>> &get_parameters() const;
    void set_parameters(const std::vector<std::string, std::allocator<std::string>> &parameters);
    
    const std::string &get_user_name() const;
    void set_user_name(const std::string &user_name);

protected:
    void ClearErrmsg();
    void SetCompilerErrmsg() noexcept;
    std::string GetRandomName();
    bool DoFork(const std::string &execute_file);

    std::string _user_name;
    std::string _file_path;
    std::string _err_buff;
    std::vector<std::string> _parameters;
    PipeManage _pipe_fd;
    std::string _tmp_path;
    ResourceLimit _resource;
};

class CppCompiler : public Compiler
{
public:
    CppCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path);
    
    virtual std::string DoCompiler();
};

class CCompiler : public Compiler
{
public:
    CCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path);
    
    virtual std::string DoCompiler();
};

class JavaCompiler : public Compiler
{
public:
    JavaCompiler(const std::string &user_name, const std::string &file_path, const std::vector<std::string> &parameters, const std::string &tmp_path);
    
    virtual std::string DoCompiler();
};

} // end of namespace guatoj

#endif // GUATOJ_JUDGEEND_SRC_COMPILER_H_