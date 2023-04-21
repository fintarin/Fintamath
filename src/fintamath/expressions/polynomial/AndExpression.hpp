#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression>, public ILogicNegatableExpression {
public:
  explicit AndExpression(const ArgumentsPtrVector &children);

  ArgumentPtr logicNegate() const override;

protected:
  ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  bool isComparableOrderInversed() const override;
};

}