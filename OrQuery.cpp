#include "OrQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "TextQuery.h"

OrQuery::OrQuery(std::shared_ptr<QueryBase> left, std::shared_ptr<QueryBase> right) :
	BinaryQuery(left, right, "|") { }

Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<QueryBase>(new OrQuery(lhs.query, rhs.query));
}

QueryResult OrQuery::evaluate(const TextQuery& text) const
{
	// virtual calls through the Query members, lhs and rhs
	// the calls to eval return the QueryResult for each operand
	auto right = rhs->evaluate(text), left = lhs->evaluate(text);
	// copy the line numbers from the left-hand operand into the result set
	auto ret_lines = std::make_shared<std::set<size_t>>(right.begin(), right.end());
	// insert lines from the right- left-hand operand
	ret_lines->insert(left.begin(), left.end());
	// return the new QueryResult representing the union of lhs and rhs
	return QueryResult(rep(), ret_lines, left.get_file());
}