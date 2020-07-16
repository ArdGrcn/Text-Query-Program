#include "AndQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include <algorithm>
#include <iterator>

AndQuery::AndQuery(std::shared_ptr<QueryBase> left, std::shared_ptr<QueryBase> right) :
	BinaryQuery(left, right, "&") { }

Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<QueryBase>(new AndQuery(lhs.query, rhs.query));
}

// returns the intersection of its operands' result sets
QueryResult AndQuery::evaluate(const TextQuery& text) const
{
	// virtual calls through the Query operands to get result sets for the operands
	auto left = lhs->evaluate(text), right = rhs->evaluate(text);
	// set to hold the intersection of left and right
	auto ret_lines = std::make_shared<std::set<size_t>>();
	// writes the intersection of two ranges to a destination iterator
	// destination iterator in this call adds elements to ret
	std::set_intersection(left.begin(), left.end(), 
		right.begin(), right.end(), 
		std::inserter(*ret_lines, ret_lines->begin())
	);
	return QueryResult(rep(), ret_lines, left.get_file());
}