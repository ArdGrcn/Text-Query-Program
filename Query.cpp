#include "Query.h"
#include "QueryBase.h"
#include "WordQuery.h"
#include "QueryResult.h"

Query::Query(const std::string& s) : query(new WordQuery(s)) { }

Query::Query(std::shared_ptr<QueryBase> q) : query(q) { }

std::string Query::rep()
{
	return query->rep();
}

QueryResult Query::evaluate(const TextQuery& t) const
{
	return query->evaluate(t);
}