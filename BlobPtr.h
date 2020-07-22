#pragma once


#include <memory>
#include <stdexcept>
#include <vector>

template <typename> class Blob;
template <typename T> class BlobPtr;
template <typename T> bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator!=(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T> class BlobPtr
{
    friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
    friend bool operator!=<T>(const BlobPtr<T>&, const BlobPtr<T>&);

public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T>&, size_t = 0);
    T& deref() const;
    BlobPtr& incr();
    bool equal(BlobPtr& rhs) const { return this->curr == rhs.curr; }
    BlobPtr& operator++(); // pre-fix operators
    BlobPtr& operator--();
    BlobPtr& operator++(int); // post-fix operators
    BlobPtr& operator--(int);
    BlobPtr operator+(const int) const;
    BlobPtr operator-(const int) const;
    BlobPtr& operator+=(const int);
    BlobPtr& operator-=(const int);
    T& operator*() const;
    T* operator->() const;

private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T> BlobPtr<T>::BlobPtr(Blob<T>& a, size_t sz) : wptr(a.data), curr(sz) { }

template <typename T> std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string& msg) const
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

template <typename T> T& BlobPtr<T>::deref() const
{
    auto p = check(curr, "Dereferencing past end.");
    return (*p)[curr];
}

template <typename T> BlobPtr<T>& BlobPtr<T>::incr()
{
    check(curr, "Incrementing past end of StrBlobPtr.");
    ++curr;
    return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator++()
{
    check(curr, "Incrementing past end of StrBlobPtr.");
    ++curr;
    return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "Decrementing before begin of StrBlobPtr."); // if curr was already 0, it is now a very large number
    return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator++(int) // post-fix
{
    auto ret = *this;
    ++* this;
    return ret;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator--(int) // post-fix
{
    auto ret = *this;
    --* this;
    return ret;
}

template <typename T> BlobPtr<T> BlobPtr<T>::operator+(const int rhs) const
{
    auto ret = *this;
    ret += rhs;
    return ret;
}

template <typename T> BlobPtr<T> BlobPtr<T>::operator-(const int rhs) const
{
    auto ret = *this;
    ret -= rhs;
    return ret;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator+=(const int rhs)
{
    check(curr, "Incrementing past end of StrBlobPtr.");
    curr += rhs;
    return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator-=(const int rhs)
{
    curr -= rhs;
    check(curr, "Decrementing before begin of StrBlobPtr.");
    return *this;
}

template <typename T> T& BlobPtr<T>::operator*() const
{
    auto p = check(curr, "Dereferencing past end.");
    return (*p)[curr];
}

template <typename T> T* BlobPtr<T>::operator->() const
{
    return &this->operator*();
}