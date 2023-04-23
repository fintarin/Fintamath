#pragma once

#include "fintamath/expressions/IInvertableExpression.hpp"
#include "fintamath/expressions/INegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>,
                      public INegatableExpression,
                      public IInvertableExpression {
public:
  explicit MulExpression(const ArgumentsPtrVector &children);

  ArgumentPtr negate() const override;

  ArgumentPtr invert() const override;

  string toString() const override;

protected:
  FunctionsVector getSimplifyFunctions() const override;

  bool isTermsOrderInversed() const override;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should not swap the arguments
   * @return  1 if we should swap the arguments
   * @return  0 if this comparator fails
   */
  int comparatorOverride(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const override;

private:
  string childToString(const ArgumentPtr &inChild, bool isFirst = false) const override;

  static ArgumentPtr simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr multiplicateBraces(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value);
};

}