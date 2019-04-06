#include "resource_limit.h"

namespace guatoj
{

ResourceLimit::ResourceLimit() : _rp(std::make_shared<rlimit>()) 
{

}

ResourceLimit::~ResourceLimit()
{

}

void ResourceLimit::SetResource(int resource, long long value_cur, long long value_max)
{
    _rp->rlim_cur = value_cur;
    _rp->rlim_max = value_max;
    setrlimit(resource, _rp.get());
}

std::pair<long long, long long> ResourceLimit::GetResource(int resource)
{
    getrlimit(resource, _rp.get());
    return {_rp->rlim_cur, _rp->rlim_max};
}

} // end of namespace guatoj