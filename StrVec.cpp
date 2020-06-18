#include "StrVec.h"


StrVec::StrVec(std::initializer_list<std::string> sl)
{
    auto data = alloc_n_copy(sl.begin(), sl.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept
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

StrVec& StrVec::operator=(std::initializer_list<std::string> il)
{
    // alloc_n_copy allocates space and copies elements from the given range
    auto data = alloc_n_copy(il.begin(), il.end());
    free(); // destroy the elements in this object and free the space
    elements = data.first; // update data members to point to the new space
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec()
{
    free();
}

std::string& StrVec::operator[](std::size_t n)
{
    return elements[n];
}

const std::string& StrVec::operator[](std::size_t n) const
{
    return elements[n];
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    reserve(newcapacity);
}

void StrVec::reserve(size_t n)
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

void StrVec::resize(size_t n)
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

void StrVec::push_back(const std::string &s)
{
    check_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
    check_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);

    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        std::for_each(elements, first_free, [this] (std::string &p) { alloc.destroy(&p); });
        alloc.deallocate(elements, cap - elements);
    }
}