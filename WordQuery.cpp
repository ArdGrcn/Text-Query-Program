#include "WordQuery.h"
#include "TextQuery.h"
#include "QueryResult.h"

WordQuery::WordQuery(const std::string& s) : query_word(s) { }

QueryResult WordQuery::evaluate(const TextQuery& t) const
{
	return t.query(query_word);
}