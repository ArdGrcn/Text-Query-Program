#pragma once


#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
    friend StrBlobPtr;
    friend ConstStrBlobPtr;

public:
    typedef std::vector<std::string>::size_type size_type;

    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
    StrBlob(const StrBlob& a) : data(std::make_shared<std::vector<std::string>>(*a.data)) { }
    StrBlob& operator=(const StrBlob&);
    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string& t) { data->push_back(t); }
    void pop_back();
    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;
    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr begin() const;
    ConstStrBlobPtr end() const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
};
