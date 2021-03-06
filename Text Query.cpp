#include "TextQuery.h"
#include "QueryResult.h"
#include "Vec.h"
#include <algorithm>
#include <sstream>

QueryResult TextQuery::query(const std::string& word_to_query) const
{
    static std::shared_ptr<std::set<size_t>> noData(
        new std::set<size_t>);

    auto found = result.find(word_to_query);
    if (found == result.cend())
    {
        std::cout << word_to_query + " not found.\n";
        return QueryResult(word_to_query, noData, input_text);
    }

    return QueryResult(word_to_query, found->second, input_text);
}


TextQuery::TextQuery(std::ifstream& infile) : input_text(std::make_shared<Vec<std::string>>())
{
    size_t lineNo = 1;
    for (std::string line; std::getline(infile, line); ++lineNo)
    {
        input_text->push_back(line);
        std::istringstream line_stream(line);
        for (std::string text, word; line_stream >> text; word.clear())
        {
            // avoid read a word followed by punctuation(such as: word, )
            std::remove_copy_if(text.begin(), text.end(), std::back_inserter(word), ispunct);
            // use reference avoid count of shared_ptr add.
            auto& result_ref = result[word];
            if (!result_ref)
                result_ref.reset(new std::set<size_t>);
            result_ref->insert(lineNo);
        }
    }
}