#pragma once

#include <iostream>
#include <memory>
#include <set>
#include <string>

class TextQuery;
template <typename> class Vec;

class QueryResult
{
    friend std::ostream& print(std::ostream& os, QueryResult result);

public:
    QueryResult() = default;
    QueryResult(
        const std::string& s,
        std::shared_ptr<std::set<size_t>> lns,
        std::shared_ptr<Vec<std::string>> b
    ) : query_name(s), lines(lns), input_text(b) { }

    // returns a reference to word count
    std::set<size_t>::iterator begin();
    std::set<size_t>::iterator end();
    std::shared_ptr<Vec<std::string>> get_file();

private:
    std::string query_name;
    std::shared_ptr<std::set<size_t>> lines;
    std::shared_ptr<Vec<std::string>> input_text;
};