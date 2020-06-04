#include "StrBlob.h"
#include "StrBlobPtr.h"


StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz) : wptr(a.data), curr(sz) { }

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
    auto ret = wptr.lock();
    if (!ret)
    {
        throw std::runtime_error("Unbound StrBlobPtr.");
    }
    if (i >= ret->size())
    {
        throw std::out_of_range(msg);
    }
    return ret;
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "Dereference past end.");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "Increment past the end of StrBlobPtr.");
    ++curr;
    return *this;
}
