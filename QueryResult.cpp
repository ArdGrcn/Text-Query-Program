#include "QueryResult.h"
#include "StrVec.h"

std::ostream& print(std::ostream& os, QueryResult result)
{
    os << result.query_name << " occurs " <<
        result.count_and_lines->first <<
        (result.count_and_lines->first > 1 ? " times" : " time") << std::endl;
    for (auto i : result.count_and_lines->second)
        os << "\t(line " << i << ") " << *(result.input_text->begin() + (i - 1)) << std::endl;
    return os;
}


std::set<QueryResult::LineNo>::iterator QueryResult::begin()
{
    return count_and_lines->second.begin();
}


std::set<QueryResult::LineNo>::iterator QueryResult::end()
{
    return count_and_lines->second.end();
}


std::shared_ptr<StrVec> QueryResult::get_file()
{
    return input_text;
}