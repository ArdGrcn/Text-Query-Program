#pragma once

#include <string>

class Query;
class QueryResult;
class TextQuery;

class QueryBase
{
	friend class Query;
public: // TODO check wheter to use friend or expose implementation
	// evaluate returns the QueryResult that matches this Query
	virtual QueryResult evaluate(const TextQuery&) const = 0;
	// rep is a string representation of the query
	virtual std::string rep() const = 0;
protected:
	virtual ~QueryBase() = default;
private:
};