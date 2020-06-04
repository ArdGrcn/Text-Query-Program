#include "TextQuery.h"
#include "QueryResult.h"


QueryResult TextQuery::query(const std::string& word_to_query)
{
    static std::shared_ptr<std::pair<size_t, std::set<TextQuery::LineNo>>> noData(new std::pair<size_t, std::set<TextQuery::LineNo>>);

    auto found = result.find(word_to_query);
    if (found == result.cend())
    {
        std::cout << "Word not found.\n";
        return QueryResult(word_to_query, noData, input_text);
    }

    return QueryResult(word_to_query, found->second, input_text);
}


TextQuery::TextQuery(std::ifstream& infile)
{
    LineNo lineNo = 1;
    for (std::string line; std::getline(infile, line); ++lineNo)
    {
        input_text.push_back(line);
        std::istringstream line_stream(line);
        for (std::string text, word; line_stream >> text; word.clear())
        {
            // avoid read a word followed by punctuation(such as: word, )
            std::remove_copy_if(text.begin(), text.end(), std::back_inserter(word), ispunct);
            // use reference avoid count of shared_ptr add.
            auto& nos = result[word];
            if (!nos)
                nos.reset(new std::pair<size_t, std::set<TextQuery::LineNo>>);
            ++nos->first;
            nos->second.insert(lineNo);
        }
    }
}
