//
// Created by 程杰仕 on 2018/6/4.
//

#ifndef OJ_KERNEL_COMPARE_H
#define OJ_KERNEL_COMPARE_H

#include <string>
#include <vector>
#include "OJlib.h"
#include "single_pipe.h"

namespace guatoj
{

class Compare
{
public:
    Compare(const std::string &input_dir, const std::string &output_dir, const std::string &process_path);
    ~Compare();

    state run_cstyle_compare();
    state run_java_compare(const std::string &interpreter);


    void reset_target(const std::string &input_dir, const std::string &output_dir, const std::string &process_path);

    // get function
    const std::string &get_input_dir() const;

    const std::string &get_standard_dir() const;

    const std::string &get_process_path() const;

private:
    state run_compare(const std::vector<std::string> &run_argvs);
    
    const std::vector<std::string> get_input_files() const ;
    const std::vector<std::string> get_standard_files() const;
    const std::vector<std::string> get_file_vec(const std::string &path) const;

    std::string _input_dir;
    std::string _standard_dir;
    std::string _process_path;
    single_pipe out_pipe;
    single_pipe err_pipe;
};

} //enf of namespace guatoj

#endif //OJ_KERNEL_COMPARE_H
