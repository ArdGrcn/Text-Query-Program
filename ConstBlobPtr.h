#pragma once


#include <memory>
#include <stdexcept>
#include <vector>

template <typename> class Blob;
template <typename T> class ConstBlobPtr;
template <typename T> bool operator==(const ConstBlobPtr<T>&, const ConstBlobPtr<T>&);
template <typename T> bool operator!=(const ConstBlobPtr<T>&, const ConstBlobPtr<T>&);

template <typename T> class ConstBlobPtr
{
    friend bool operator==<T>(const ConstBlobPtr<T>&, const ConstBlobPtr<T>&);
    friend bool operator!=<T>(const ConstBlobPtr<T>&, const ConstBlobPtr<T>&);
public:
    ConstBlobPtr() : curr(0) {}
    ConstBlobPtr(const Blob<T>&, size_t = 0);

    const T& deref() const;
    ConstBlobPtr& incr();
    bool equal(const ConstBlobPtr& rhs) const { return this->curr == rhs.curr; }
    const T& operator*() const;
    const T* operator->() const;

private:
    std::shared_ptr<const std::vector<T>> check(std::size_t, const std::string&) const;

    std::weak_ptr<const std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T> ConstBlobPtr<T>::ConstBlobPtr(const Blob<T>& a, size_t sz) : wptr(a.data), curr(sz) { }

template <typename T> std::shared_ptr<const std::vector<T>> ConstBlobPtr<T>::check(std::size_t i, const std::string& msg) const
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

template <typename T> const T& ConstBlobPtr<T>::deref() const
{
    auto p = check(curr, "Dereference past end.");
    return (*p)[curr];
}

template <typename T> ConstBlobPtr<T>& ConstBlobPtr<T>::incr()
{
    check(curr, "Increment past the end of StrBlobPtr.");
    ++curr;
    return *this;
}

template <typename T> const T& ConstBlobPtr<T>::operator*() const
{
    auto p = check(curr, "Dereferencing past end.");
    return (*p)[curr];
}

template <typename T> const T* ConstBlobPtr<T>::operator->() const
{
    return &this->operator*();
}