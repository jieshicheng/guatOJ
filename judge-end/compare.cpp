//
// Created by 程杰仕 on 2018/6/4.
//

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <dirent.h>
#include "compare.h"
#include <cstring>
#include <algorithm>
#include <sys/wait.h>

namespace guatoj
{

Compare::Compare(const std::string &input_dir, const std::string &output_dir, const std::string &process_path) :
        _input_dir(input_dir), _standard_dir(output_dir), _process_path(process_path),
        out_pipe(), err_pipe()
{
    append_divd(_input_dir);
    append_divd(_standard_dir);
}

Compare::~Compare()
{
    // clear elf file in here
}

const std::vector<std::string> Compare::get_standard_files() const
{
    return get_file_vec(_standard_dir);
}

const std::vector<std::string> Compare::get_input_files() const
{
    return get_file_vec(_input_dir);
}

/**
 * given a folder path
 * return all files name that under the folder except . and ..
 */
const std::vector<std::string> Compare::get_file_vec(const std::string &path) const
{
    std::vector<std::string> ans;
    if (path == "")
        return ans;

    DIR *drip;
    dirent *dp;
    drip = opendir(path.c_str());
    if (drip == nullptr)
    {
        printf("get_file_vec error: open dir error");
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
guatoj::state Compare::run_compare()
{
    /**
     * get the all of file in the input dir and out dir
     * if files are not the same, the question manage should fix this bug.
     */
    std::vector<std::string> input_file_vec = get_input_files();
    std::vector<std::string> output_file_vec = get_standard_files();

    std::sort(input_file_vec.begin(), input_file_vec.end());
    std::sort(output_file_vec.begin(), output_file_vec.end());

    if (input_file_vec != output_file_vec)
    {
        return guatoj::Answer_error;
    }

    // start execute and compare.
    pid_t pid;
    /* according to the input file. fork a process and run it */
    for (int i = 0; i != input_file_vec.size(); ++i)
    {
        if ((pid = fork()) == 0)
        {
            // child process
            int in_fd = open((_input_dir + input_file_vec[i].c_str()).c_str(), O_RDONLY);

            /* close any read pipe. because this process only do write */
            close(out_pipe.get_read_descriptor());
            close(err_pipe.get_read_descriptor());

            // redirect stdin and stdout to pipe
            dup2(in_fd, STDIN_FILENO);
            dup2(out_pipe.get_write_descriptor(), STDOUT_FILENO);
            dup2(err_pipe.get_write_descriptor(), STDERR_FILENO);
            /* then close them */
            close(in_fd);
            close(err_pipe.get_write_descriptor());
            close(out_pipe.get_write_descriptor());

            // construct run env
            std::vector<std::string> arg_vec(1);
            arg_vec[0] = _process_path;
            guatoj::execvp_vec(arg_vec);

            //process run here means error.so eixt with 1
            printf("fetal error: should't be here\n");
            _exit(1);
        }
        else
        {
            // father process
            int out_fd = open((_standard_dir + input_file_vec[i].c_str()).c_str(), O_RDONLY);

            int status;
            // run successfule. check the two file content whether equal
            if (waitpid(pid, &status, 0) != -1 && WEXITSTATUS(status) == 0)
            {
                if (guatoj::is_content_equal(out_fd, out_pipe.get_read_descriptor()))
                {
                    continue;
                }
                else
                {
                     return guatoj::Worry_ans;
                }
            }
            else
            {
                
                //if time out
                //if runtime error
            }
        }
    }
    return guatoj::Accept;
}

const std::string &Compare::get_input_dir() const
{
    return _input_dir;
}

const std::string &Compare::get_standard_dir() const
{
    return _standard_dir;
}

const std::string &Compare::get_process_path() const
{
    return _process_path;
}

void Compare::reset_target(const std::string &input_dir, const std::string &output_dir, const std::string &process_path)
{
    _input_dir = input_dir;
    _standard_dir = output_dir;
    _process_path = process_path;
}

}  // end of namespace guatoj
