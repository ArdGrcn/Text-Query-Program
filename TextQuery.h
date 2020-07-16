#pragma once


#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>


class QueryResult;
class StrVec;

class TextQuery
{
public:
    TextQuery(std::ifstream& infile);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<StrVec> input_text;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> result;
};