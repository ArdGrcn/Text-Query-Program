#include "ConstStrBlobPtr.h"
#include "StrBlob.h"


ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob& a, size_t sz) : wptr(a.data), curr(sz) { }

const std::shared_ptr<const std::vector<std::string>> ConstStrBlobPtr::check(std::size_t i, const std::string& msg) const
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

const std::string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "Dereference past end.");
    return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "Increment past the end of StrBlobPtr.");
    ++curr;
    return *this;
}