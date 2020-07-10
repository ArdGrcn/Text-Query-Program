#pragma once


#include <iostream>
#include <memory>
#include <set>
#include <string>

class TextQuery;
class StrVec;

class QueryResult
{
    friend std::ostream& print(std::ostream& os, QueryResult result);

public:
    using LineNo = size_t;
    using WordCount = size_t;
    QueryResult() = default;
    QueryResult(
        const std::string& s,
        std::shared_ptr<std::pair<WordCount, std::set<LineNo>>> pair,
        std::shared_ptr<StrVec> b
    ) : query_name(s), count_and_lines(pair), input_text(b) { }

    std::set<LineNo>::iterator begin();
    std::set<LineNo>::iterator end();
    std::shared_ptr<StrVec> get_file();

private:
    std::string query_name;
    std::shared_ptr<std::pair<WordCount, std::set<LineNo>>> count_and_lines;
    std::shared_ptr<StrVec> input_text;
};