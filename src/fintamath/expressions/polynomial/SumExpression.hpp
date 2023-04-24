#pragma once

#include "fintamath/expressions/INegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatableExpression {
public:
  explicit SumExpression(const ArgumentsPtrVector &children);

  ArgumentPtr negate() const override;

protected:
  FunctionsVector getSimplifyFunctions() const override;

private:
  string childToString(const ArgumentPtr &inChild, bool isFirst = false) const override;

  static ArgumentPtr simplifyNumbers(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegations(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr sumRates(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &inChild);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);
};

}