#pragma once


#include "StrBlob.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

class QueryResult;

class TextQuery
{
public:
    using LineNo = std::vector<std::string>::size_type;
    TextQuery(std::ifstream& infile);
    QueryResult query(const std::string&);

private:
    StrBlob input_text;
    std::map<std::string, std::shared_ptr<std::pair<size_t, std::set<TextQuery::LineNo>>>> result;
};
