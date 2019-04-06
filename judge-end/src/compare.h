//
// Created by 程杰仕 on 2018/6/4.
//

#ifndef GUATOJ_JUDGEEND_SRC_COMPARE_H_
#define GUATOJ_JUDGEEND_SRC_COMPARE_H_

#include "lib/oj_lib.h"
#include "pipe_manage.h"
#include "resource_limit.h"
#include "question.h"

#include <string>
#include <vector>


namespace guatoj
{

class Compare
{
public:
    Compare(const std::string &process_path, const Question &ques);
    ~Compare();

    SubmitState RunCstyleCompare();
    SubmitState RunJavaCompare();

    void ResetTarget(const std::string &process_path, const Question &ques);

    // get function

    const Question &get_question() const ;
    const std::string &get_process_path() const ;

    void set_question(const Question &ques);
    void set_process_path(const std::string &str);

private:
    SubmitState RunCompare(const std::vector<std::string> &run_argvs, bool is_cstyle);
    
    const std::vector<std::string> GetInputFiles() const ;
    const std::vector<std::string> GetOutputFiles() const;
    const std::vector<std::string> GetFileVec(const std::string &path) const;

    Question _question;
    std::string _process_path;
    PipeManage _out_pipe;
    PipeManage _err_pipe;
    ResourceLimit _resource;
};

} //enf of namespace guatoj

#endif // GUATOJ_JUDGEEND_SRC_COMPARE_H_
