#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IOperator &oper, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  string toString() const override;

  void markAsSolution();

protected:
  ArgumentPtr preSimplify() const override;

private:
  bool isSolution = false;
};

}