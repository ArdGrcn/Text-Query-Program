#include "StrBlob.h"
#include "StrBlobPtr.h"
#include "ConstStrBlobPtr.h"

StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
    return *this;
}

void StrBlob::check(size_type i, const std::string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string& StrBlob::front() const // const overload
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::back() const // const overload
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

ConstStrBlobPtr StrBlob::begin() const
{
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::end() const
{
    return ConstStrBlobPtr(*this, data->size());
}