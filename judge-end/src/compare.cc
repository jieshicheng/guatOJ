//
// Created by 程杰仕 on 2018/6/4.
//
#include "compare.h"
#include <cstring>

#include <glog/logging.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

namespace guatoj
{

Compare::Compare(const std::string &process_path, const Question &ques) :
        _question(ques), _process_path(process_path), _out_pipe(), _err_pipe(), _resource()
{
}

Compare::~Compare()
{
}

const std::vector<std::string> Compare::GetOutputFiles() const
{
    return GetFileVec(_question.get_output_dir());
}

const std::vector<std::string> Compare::GetInputFiles() const
{
    return GetFileVec(_question.get_input_dir());
}

/**
 * given a folder path
 * return all files name that under the folder except . and ..
 */
const std::vector<std::string> Compare::GetFileVec(const std::string &path) const
{
    std::vector<std::string> ans;
    if (path == "")
        return ans;

    DIR *drip;
    dirent *dp;
    drip = opendir(path.c_str());
    if (drip == nullptr)
    {
        LOG(ERROR) << "get_file_vec error: open dir error";
        return ans;
    }

    while (true)
    {
        errno = 0;
        dp = readdir(drip);
        if (dp == nullptr)
            break;
        // if file is . or ..,dont't put it
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;
        ans.push_back(std::string(dp->d_name));
    }
    closedir(drip);
    return ans;
}

/**
 * @return Accept Time_out Worry_ans Runtime_error
 */
SubmitState Compare::RunCompare(const std::vector<std::string> &run_argvs, bool is_cstyle)
{
    /**
     * get the all of file in the input dir and out dir
     * if files are not the same, the question manage should fix this bug.
     */
    std::vector<std::string> input_file_vec = GetInputFiles();
    std::vector<std::string> output_file_vec = GetOutputFiles();

    std::sort(input_file_vec.begin(), input_file_vec.end());
    std::sort(output_file_vec.begin(), output_file_vec.end());

    if (input_file_vec != output_file_vec)
    {
        return AnswerError;
    }

    // start execute and compare.
    pid_t pid;
    /* according to the input file. fork a process and run it */
    for (int i = 0; i != input_file_vec.size(); ++i)
    {
        if ((pid = fork()) == 0)
        {
            // child process
            int in_fd = open((_question.get_input_dir() + input_file_vec[i].c_str()).c_str(), O_RDONLY);

            /* close any read pipe. because this process only do write */
            close(_out_pipe.get_read_fd());
            close(_err_pipe.get_read_fd());

            // redirect stdin and stdout to pipe
            dup2(in_fd, STDIN_FILENO);
            dup2(_out_pipe.get_write_fd(), STDOUT_FILENO);
            dup2(_err_pipe.get_write_fd(), STDERR_FILENO);
            /* then close them */
            close(in_fd);
            close(_err_pipe.get_write_fd());
            close(_out_pipe.get_write_fd());

            //set resource limit
            /*if (is_cstyle)
            {
                _resource.set_AS_max(_ques.get_memory_limit());
                _resource.set_CPU_max(_ques.get_cpu_limit());
            }
            else
            {
                _resource.set_CPU_max(_ques.get_cpu_limit() * 2);
            }
            _resource.set_CORE_max(0);
            */

            ExecvpVec(run_argvs);

            //process run here means error.so eixt with 1
            LOG(FATAL) << "fetal error: should't be here";
            _exit(1);
        }
        else
        {
            // father process
            int out_fd = open((_question.get_output_dir() + input_file_vec[i].c_str()).c_str(), O_RDONLY);

            int status;
            // run successfule. check the two file content whether equal
            if (waitpid(pid, &status, 0) == -1)
            {
                LOG(ERROR) << "waitpid return -1, errno: " << errno;
                return SystemError;
            }
            else if (WIFSIGNALED(status))
            {
                // by killed
                LOG(INFO) << "process killed by sign: " << WTERMSIG(status);
                if (WTERMSIG(status) == SIGXCPU)
                    return TimeOut;
                else
                    return RunTimeError;
            }
            else if (WIFSTOPPED(status))
            {
                // by stop
                LOG(INFO) << "process stoped by sign: " << WSTOPSIG(status);
                return RunTimeError;
            }
            else if (WIFEXITED(status)) //&& WEXITSTATUS(status) == 0)
            {
                // correct exit
                if (guatoj::IsContentEqual(out_fd, _out_pipe.get_read_fd()))
                {
                    continue;
                }
                else
                {
                    return WorryAns;
                }
            }
            else
            {
                LOG(ERROR) << "user process exit unknow error";
                return SystemError;
            }
        }
    }
    return Accept;
}

SubmitState Compare::RunCstyleCompare()
{
    std::vector<std::string> vec;
    vec.push_back(_process_path);
    return RunCompare(vec, true);
}

SubmitState Compare::RunJavaCompare()
{
    std::string file_name = _process_path.substr(_process_path.find_last_of('/') + 1, _process_path.find_last_of('.') - _process_path.find_last_of('/') - 1);
    std::vector<std::string> vec;
    vec.push_back("java");
    vec.push_back("-cp");
    vec.push_back(_process_path.substr(0, _process_path.find_last_of('/')));
    vec.push_back(file_name);
    return RunCompare(vec, false);
}

const Question &Compare::get_question() const
{
    return _question;
}

const std::string &Compare::get_process_path() const
{
    return _process_path;
}

void Compare::ResetTarget(const std::string &process_path, const Question &ques)
{
    _process_path = process_path;
    _question = ques;
}

void Compare::set_process_path(const std::string &str)
{
    _process_path = str;
}

void Compare::set_question(const Question &ques)
{
    _question = ques;
}

}  // end of namespace guatoj