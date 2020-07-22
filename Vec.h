#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>


template <typename T> class Vec
{
public:
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    Vec(std::initializer_list<T>);
    Vec(const Vec&);
    Vec(Vec&&) noexcept;
    Vec& operator=(const Vec&);
    Vec& operator=(Vec&&) noexcept;
    Vec& operator=(std::initializer_list<T>);
    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;
    ~Vec();

    void push_back(const T&);
    void push_back(T&&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    void reserve(size_t);
    void resize(size_t);
    T* begin() const { return elements; }
    T* end() const { return first_free; }

private:
    std::allocator<T> alloc;

    void check_n_alloc() { if (size() == capacity()) reallocate(); }
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();
    void reallocate();

    T *elements;
    T *first_free;
    T *cap;
};

template <typename T> Vec<T>::Vec(std::initializer_list<T> sl)
{
    auto data = alloc_n_copy(sl.begin(), sl.end());
    elements = data.first;
    first_free = cap = data.second;
}

template <typename T> Vec<T>::Vec(const Vec& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T> Vec<T>::Vec(Vec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

template <typename T> Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T> Vec<T>& Vec<T>::operator=(Vec&& rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;

        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template <typename T> Vec<T>& Vec<T>::operator=(std::initializer_list<T> il)
{
    // alloc_n_copy allocates space and copies elements from the given range
    auto data = alloc_n_copy(il.begin(), il.end());
    free(); // destroy the elements in this object and free the space
    elements = data.first; // update data members to point to the new space
    first_free = cap = data.second;
    return *this;
}

template <typename T> Vec<T>::~Vec()
{
    free();
}

template <typename T> T& Vec<T>::operator[](std::size_t n)
{
    return elements[n];
}

template <typename T> const T& Vec<T>::operator[](std::size_t n) const
{
    return elements[n];
}

template <typename T> void Vec<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    reserve(newcapacity);
}

template <typename T> void Vec<T>::reserve(size_t n)
{
    if (n <= capacity())
    {
        return;
    }

    auto newdata = alloc.allocate(n);

    auto dest = newdata;
    auto elem = elements;

    for (size_t i = 0; i != size(); ++i)
    {
        alloc.construct(dest++, std::move(*elem++));
    }

    free();
    elements = newdata;
    first_free = dest;
    cap = elements + n;
}

template <typename T> void Vec<T>::resize(size_t n)
{
    if (size() < n)
    {
        reserve(n);
    }
    else if (size() > n)
    {
        // only copy the first n elements
        auto newend = elements + n;
        auto data = alloc_n_copy(elements, newend);
        free();
        elements = data.first;
        cap = first_free = data.second;
    }
    else
    {
        return;
    }
}

template <typename T> void Vec<T>::push_back(const T& s)
{
    check_n_alloc();
    alloc.construct(first_free++, s);
}

template <typename T> void Vec<T>::push_back(T&& s)
{
    check_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

template <typename T> std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* b, const T* e)
{
    auto data = alloc.allocate(e - b);

    return { data, std::uninitialized_copy(b, e, data) };
}

template <typename T> void Vec<T>::free()
{
    if (elements)
    {
        std::for_each(elements, first_free, [this](std::string& p) { alloc.destroy(&p); });
        alloc.deallocate(elements, cap - elements);
    }
}