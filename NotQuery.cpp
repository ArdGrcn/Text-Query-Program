#include "NotQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include "Vec.h"


NotQuery::NotQuery(std::shared_ptr<QueryBase> q) : query(q) { }

Query operator~(const Query& operand)
{
	return std::shared_ptr<QueryBase>(new NotQuery(operand.query));
}

std::string NotQuery::rep() const
{
	return "~(" + query->rep() + ")";
}

// returns the lines not in its operand's result set
QueryResult NotQuery::evaluate(const TextQuery& text) const
{
	auto result = query->evaluate(text);
	// start out with an empty result set
	auto ret_lines = std::make_shared<std::set<size_t>>();
	// we have to iterate through the lines on which our operand appears
	auto beg = result.begin(), end = result.end();
	// for each line in the input file, if that line is not in result,
	// add that line number to ret_lines
	auto sz = result.get_file()->size();
	for (size_t n = 1; n != sz; ++n) {
		// if we haven't processed all the lines in result
		// check whether this line is present
		if (beg == end || *beg != n)
			ret_lines->insert(n); // if not in result, add this line
		else if (beg != end)
			++beg; // otherwise get the next line number in result if there is one
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}