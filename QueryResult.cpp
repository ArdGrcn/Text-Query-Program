#include "StrBlobPtr.h"
#include "QueryResult.h"


std::ostream& print(std::ostream& os, QueryResult result)
{
    os << result.query_name << " occurs " << result.nos->first << (result.nos->first > 1 ? " times" : " time") << std::endl;
    for (auto i : result.nos->second)
        os << "\t(line " << i << ") " << StrBlobPtr(result.input_text, i - 1).deref() << std::endl; // TODO handle pointer access
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


std::shared_ptr<StrBlob> QueryResult::get_file()
{
    return std::make_shared<StrBlob>(input_text);
}