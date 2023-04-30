#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class OrExpression : public IPolynomExpressionCRTP<OrExpression>, public ILogicNegatableExpression {
public:
  explicit OrExpression(const ArgumentsPtrVector &inChildren);

  ArgumentPtr logicNegate() const override;

protected:
  std::string childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  ArgumentPtr postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr simplifyEqual(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNot(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyAnd(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyBooleans(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}