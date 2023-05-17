#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  explicit AndExpression(const ArgumentsPtrVector &inChildren);

  // TODO!!! reimplement
  // ArgumentPtr logicNegate() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::AndExpression;
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr simplifyBooleans(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyEqual(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNot(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyOr(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);
};

}