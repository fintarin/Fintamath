#pragma once

#include "fintamath/expressions/INegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatableExpression {
public:
  explicit MulExpression(const ArgumentsPtrVector &inChildren);

  ArgumentPtr negate() const override;

protected:
  ArgumentPtr postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  bool isTermsOrderInversed() const override;

private:
  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  static ArgumentPtr simplifyNumbers(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegations(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulPolynoms(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulRates(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);

private:
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions;
};

}