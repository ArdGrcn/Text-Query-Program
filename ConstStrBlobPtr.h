#pragma once


#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlob;

class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob&, size_t = 0);

    const std::string& deref() const;
    ConstStrBlobPtr& incr();
    bool equal(const ConstStrBlobPtr& rhs) const { return this->curr == rhs.curr; }
    const std::string& operator*() const;
    const std::string* operator->() const;

private:
    std::shared_ptr<const std::vector<std::string>> check(std::size_t, const std::string&) const;

    std::weak_ptr<const std::vector<std::string>> wptr;
    std::size_t curr;
};