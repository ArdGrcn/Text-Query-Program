#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <utility>


class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    void reserve(size_t);
    void resize(size_t);
    std::string* begin() const { return elements; }
    std::string* end() const { return first_free; }

private:
    std::allocator<std::string> alloc;

    void check_n_alloc() { if (size() == capacity()) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();

    std::string *elements;
    std::string *first_free;
    std::string *cap;
};