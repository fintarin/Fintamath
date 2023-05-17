#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression> {
public:
  explicit MulExpression(const ArgumentsPtrVector &inChildren);

  // TODO!!! reimplement
  // ArgumentPtr negate() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::MulExpression;
  }

protected:
  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  bool isTermsOrderInversed() const override;

private:
  static ArgumentPtr simplifyNumbers(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegations(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulPolynoms(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulRates(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);
};

}