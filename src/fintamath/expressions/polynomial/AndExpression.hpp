#pragma once

#include "fintamath/expressions/interfaces/ILogicNegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression>, public ILogicNegatable {
public:
  explicit AndExpression(const ArgumentsPtrVector &children);

  ArgumentPtr logicNegate() const override;

protected:
  // TODO: refactor, implement other logic functionaluty
  ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  bool isComparableOrderInversed() const override;
};

}