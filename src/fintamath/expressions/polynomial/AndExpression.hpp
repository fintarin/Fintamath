#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression>, public ILogicNegatableExpression {
public:
  explicit AndExpression(const ArgumentsPtrVector &inChildren);

  ArgumentPtr logicNegate() const override;

protected:
  std::string childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  ArgumentPtr postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr simplifyEqual(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNot(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}