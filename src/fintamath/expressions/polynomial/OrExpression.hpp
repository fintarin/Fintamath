#pragma once

#include "fintamath/expressions/interfaces/ILogicNegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {

class OrExpression : public IPolynomExpressionCRTP<OrExpression>, public ILogicNegatable {
public:
  explicit OrExpression(const ArgumentsPtrVector &children);

  ArgumentPtr logicNegate() const override;

protected:
  ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;
};

}