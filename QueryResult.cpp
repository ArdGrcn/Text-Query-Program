#include "QueryResult.h"
#include "StrVec.h"

std::ostream& print(std::ostream& os, QueryResult result)
{
    os << result.query_name << " occurs " << result.nos->first << (result.nos->first > 1 ? " times" : " time") << std::endl;
    for (auto i : result.nos->second)
        os << "\t(line " << i << ") " << *(result.input_text->begin() + (i - 1)) << std::endl;
    return os;
}


std::set<QueryResult::LineNo>::iterator QueryResult::begin()
{
    return nos->second.begin();
}


std::set<QueryResult::LineNo>::iterator QueryResult::end()
{
    return nos->second.end();
}


std::shared_ptr<StrVec> QueryResult::get_file()
{
    return input_text;
}