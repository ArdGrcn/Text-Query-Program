#include "StrBlobPtr.h"
#include "StrBlob.h"


StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz) : wptr(a.data), curr(sz) { }

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
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
    check(curr, "Incrementing past end of StrBlobPtr.");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "Incrementing past end of StrBlobPtr.");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    --curr;
    check(curr, "Decrementing before begin of StrBlobPtr."); // if curr was already 0, it is now a very large number
    return *this;
}

StrBlobPtr& StrBlobPtr::operator++(int) // post-fix
{
    auto ret = *this;
    ++* this;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator--(int) // post-fix
{
    auto ret = *this;
    --* this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator+(const int rhs) const
{
    auto ret = *this;
    ret += rhs;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-(const int rhs) const
{
    auto ret = *this;
    ret -= rhs;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator+=(const int rhs)
{
    check(curr, "Incrementing past end of StrBlobPtr.");
    curr += rhs;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-=(const int rhs)
{
    curr -= rhs;
    check(curr, "Decrementing before begin of StrBlobPtr.");
    return *this;
}