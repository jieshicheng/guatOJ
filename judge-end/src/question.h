#ifndef GUATOJ_JUDGEEND_SRC_QUESTION_H_
#define GUATOJ_JUDGEEND_SRC_QUESTION_H_

#include "lib/oj_lib.h"

#include <string>

namespace guatoj
{

class Question
{
public:
    Question(const std::string &in, const std::string &out, long long mem_l, long long cpu_l);

    ~Question();

    std::string get_input_dir() const ;
    std::string get_output_dir() const ;
    long long get_memory_limit() const ;
    long long get_cpu_limit() const ;

    void set_input_dir(const std::string &in);
    void set_output_dir(const std::string &out);
    void set_memory_limit(long long v);
    void set_cpu_limit(long long v);

private:
    std::string _input_dir;
    std::string _output_dir;
    long long _memory_limit;
    long long _cpu_limit;
};

} // namespace of guatoj

#endif // GUATOJ_JUDGEEND_SRC_QUESTION_H_