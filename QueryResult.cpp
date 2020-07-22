#include "QueryResult.h"
#include "Vec.h"

std::ostream& print(std::ostream& os, QueryResult result)
{
    os << result.query_name << " appears on " <<
        result.lines->size() <<
        (result.lines->size() > 1 ? " lines" : " line") << std::endl;
    for (auto i : *result.lines)
        os << "\t(line " << i << ") " << *(result.input_text->begin() + (i - 1)) << std::endl;
    return os;
}

std::set<size_t>::iterator QueryResult::begin()
{
    return lines->begin();
}

std::set<size_t>::iterator QueryResult::end()
{
    return lines->end();
}

std::shared_ptr<Vec<std::string>> QueryResult::get_file()
{
    return input_text;
}