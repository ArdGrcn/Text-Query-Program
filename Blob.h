#pragma once


#include <memory>
#include <stdexcept>
#include <vector>

template <typename> class BlobPtr;
template <typename> class ConstBlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator!=(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob
{
    friend BlobPtr<T>;
    friend ConstBlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    friend bool operator!=<T>(const Blob<T>&, const Blob<T>&);

public:
    typedef typename std::vector<T>::size_type size_type;

    Blob();
    Blob(const Blob<T>&);
    Blob<T>& operator=(const Blob<T>&);
    Blob(std::initializer_list<T>);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T& s) { data->push_back(s); }
    void push_back(T&& s) { data->push_back(std::move(s)); }
    void pop_back();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    BlobPtr<T> begin();
    BlobPtr<T> end();
    ConstBlobPtr<T> begin() const;
    ConstBlobPtr<T> end() const;

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string& msg) const;
};

template <typename T> Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T> Blob<T>::Blob(const Blob& a) : data(std::make_shared<std::vector<T>>(*a.data)) { }

template <typename T> Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }

template <typename T> Blob<T>& Blob<T>::operator=(const Blob& rhs)
{
    data = std::make_shared<std::vector<T>>(*rhs.data);
    return *this;
}

template <typename T> void Blob<T>::check(size_type i, const std::string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T> T& Blob<T>::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

template <typename T> T& Blob<T>::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

template <typename T> const T& Blob<T>::front() const // const overload
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

template <typename T> const T& Blob<T>::back() const // const overload
{
    check(0, "back on empty StrBlob");
    return data->back();
}

template <typename T> void Blob<T>::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

template <typename T> BlobPtr<T> Blob<T>::begin()
{
    return BlobPtr<T>(*this);
}

template <typename T> BlobPtr<T> Blob<T>::end()
{
    return BlobPtr<T>(*this, data->size());
}

template <typename T> ConstBlobPtr<T> Blob<T>::begin() const
{
    return ConstBlobPtr<T>(*this);
}

template <typename T> ConstBlobPtr<T> Blob<T>::end() const
{
    return ConstBlobPtr<T>(*this, data->size());
}