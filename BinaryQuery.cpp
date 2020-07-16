#include "BinaryQuery.h"
#include "Query.h"

BinaryQuery::BinaryQuery(std::shared_ptr<QueryBase> l, std::shared_ptr<QueryBase> r, std::string s) :
	lhs(l), rhs(r), opSym(s) { }

std::string BinaryQuery::rep() const
{
	return "(" + lhs->rep() + " " + opSym + " " + rhs->rep() + ")";
}