/**
 * created by jieshicheng.
 * 2018-12-8
 */

#ifndef GUATOJ_JUDGEEND_SRC_RESOURCE_H_
#define GUATOJ_JUDGEEND_SRC_RESOURCE_H_

#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

#include <memory>
#include <utility>

namespace guatoj
{

class ResourceLimit
{
public:
    ResourceLimit(); 

    ~ResourceLimit();

    std::pair<long long, long long> GetResource(int resource);

    void SetResource(int resource, long long value_cur, long long value_max);

private:
    std::shared_ptr<rlimit> _rp;
};

} //end of namespace guatoj

#endif //GUATOJ_JUDGEEND_SRC_RESOURCE_H_