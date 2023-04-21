#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class OrExpression : public IPolynomExpressionCRTP<OrExpression>, public ILogicNegatableExpression {
public:
  explicit OrExpression(const ArgumentsPtrVector &children);

  ArgumentPtr logicNegate() const override;

  string childToString(const ArgumentPtr &child, bool isFirst) const override;

protected:
  // TODO: refactor, implement other logic functionaluty
  ArgumentPtr preSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  ArgumentPtr postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;

  bool isComparableOrderInversed() const override;
};

}