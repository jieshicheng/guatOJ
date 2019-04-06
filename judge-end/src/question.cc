#include "question.h"
#include "lib/oj_lib.h"

namespace guatoj
{

Question::Question(const std::string &in, const std::string &out, long long mem_l, long long cpu_l) :
        _input_dir(in), _output_dir(out), _memory_limit(mem_l), _cpu_limit(cpu_l)
{
    AppendDivd(_input_dir);
    AppendDivd(_output_dir);
}

Question::~Question()
{

}

long long Question::get_cpu_limit() const
{
    return _cpu_limit;
}

std::string Question::get_input_dir() const
{
    return _input_dir;
}

long long Question::get_memory_limit() const
{
    return _memory_limit;
}

std::string Question::get_output_dir() const
{
    return _output_dir;
}

void Question::set_cpu_limit(long long v)
{
    _cpu_limit = v;
}

void Question::set_input_dir(const std::string &in)
{
    _input_dir = in;
}

void Question::set_memory_limit(long long v)
{
    _memory_limit = v;
}

void Question::set_output_dir(const std::string &out)
{
    _output_dir = out;
}

} // namespace of guatoj