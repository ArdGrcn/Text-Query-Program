#pragma once


#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlob;

class StrBlobPtr
{
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob&, size_t = 0);
    std::string& deref() const;
    StrBlobPtr& incr();
    bool equal(StrBlobPtr& rhs) const { return this->curr == rhs.curr; }
    StrBlobPtr& operator++(); // pre-fix operators
    StrBlobPtr& operator--();
    StrBlobPtr& operator++(int); // post-fix operators
    StrBlobPtr& operator--(int);
    StrBlobPtr operator+(const int) const;
    StrBlobPtr operator-(const int) const;
    StrBlobPtr& operator+=(const int);
    StrBlobPtr& operator-=(const int);
    std::string& operator*() const;
    std::string* operator->() const;

private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);