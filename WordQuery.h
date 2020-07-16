#pragma once

#include "QueryBase.h"

class Query;

class WordQuery : public QueryBase
{
	friend class Query; // Query uses the WordQuery constructor

	WordQuery(const std::string& s);

	// concrete class: WordQuery defines all inherited pure virtual functions
	QueryResult evaluate(const TextQuery&) const override;
	std::string rep() const override { return query_word; }

	std::string query_word; // word for which to search
};