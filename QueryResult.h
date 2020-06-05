#pragma once


#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class TextQuery;
class StrVec;

class QueryResult
{
    friend std::ostream& print(std::ostream& os, QueryResult result);

public:
    using LineNo = std::vector<std::string>::size_type;
    QueryResult() = default;
    QueryResult(
        const std::string& s,
        std::shared_ptr<std::pair<size_t, std::set<LineNo>>> pair,
        std::shared_ptr<StrVec> b
    ) : query_name(s), nos(pair), input_text(b) { }

    std::set<LineNo>::iterator begin();
    std::set<LineNo>::iterator end();
    std::shared_ptr<StrVec> get_file();

private:
    std::string query_name;
    std::shared_ptr<std::pair<size_t, std::set<LineNo>>> nos;
    std::shared_ptr<StrVec> input_text;
};