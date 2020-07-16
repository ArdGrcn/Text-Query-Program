#pragma once

#include "QueryBase.h"
#include "memory"

class Query;

class NotQuery : public QueryBase
{
	friend Query operator~(const Query&);

	NotQuery(std::shared_ptr<QueryBase>);

	// concrete class: NotQuery defines all inherited pure virtual functions
	std::string rep() const override;
	QueryResult evaluate(const TextQuery&) const override;

	std::shared_ptr<QueryBase> query;
};