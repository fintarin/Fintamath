#pragma once

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class SumExpression : public IPolynomExpressionCRTP<SumExpression>, public INegatable {
public:
  explicit SumExpression(const ArgumentsPtrVector &children);

  ArgumentPtr negate() const override;

protected:
  FunctionsVector getSimplifyFunctions() const override;

private:
  string childToString(const ArgumentPtr &child, bool isFirst = false) const override;

  static ArgumentPtr simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value);
};

}