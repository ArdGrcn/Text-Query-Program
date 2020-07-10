#pragma once


#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>

class QueryResult;
class StrVec;

class TextQuery
{
public:
    using LineNo = size_t;
    using WordCount = size_t;
    TextQuery(std::ifstream& infile);
    QueryResult query(const std::string&);

private:
    std::shared_ptr<StrVec> input_text;
    std::map<std::string, std::shared_ptr<std::pair<WordCount, std::set<LineNo>>>> result;
};