#pragma once

#include "BinaryQuery.h"

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);

	OrQuery(std::shared_ptr<QueryBase>, std::shared_ptr<QueryBase>);
	QueryResult evaluate(const TextQuery&) const override;
};