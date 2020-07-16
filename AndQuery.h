#pragma once

#include "BinaryQuery.h"

class Query;

class AndQuery : public BinaryQuery
{
	friend Query operator& (const Query&, const Query&);

	AndQuery(std::shared_ptr<QueryBase>, std::shared_ptr<QueryBase>);
	// concrete class: AndQuery inherits rep and defines the remaining pure virtual
	QueryResult evaluate(const TextQuery&) const override;
};