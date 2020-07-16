#pragma once

#include "QueryBase.h"
#include <memory>


class BinaryQuery : public QueryBase
{
protected:
	BinaryQuery(std::shared_ptr<QueryBase>, std::shared_ptr<QueryBase>, std::string);
	// abstract class: BinaryQuery doesn't define eval
	std::string rep() const override;
	std::shared_ptr<QueryBase> lhs, rhs; // right- and left-hand operands
	std::string opSym; // name of the operator
};