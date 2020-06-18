#include "StrBlob.h"
#include "StrBlobPtr.h"


bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return lhs.wptr.lock == rhs.wptr.lock && lhs.curr == rhs.curr;
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return !(lhs == rhs);
}

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