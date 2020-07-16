#pragma once

#include <memory>
#include <string>

class QueryBase;
class QueryResult;
class TextQuery;

class Query
{
	// these operators need access to the shared_ptr constructor
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&); // builds a new WordQuery
	// interface functions: call the corresponding Query_base operations
	QueryResult evaluate(const TextQuery&) const;
	std::string rep();
private:
	Query(std::shared_ptr<QueryBase>);

	std::shared_ptr<QueryBase> query;
};

Query operator~(const Query&);
Query operator|(const Query&, const Query&);
Query operator&(const Query&, const Query&);