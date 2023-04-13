#pragma once

#include "fintamath/expressions/interfaces/IInvertable.hpp"
#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class MulExpression : public IPolynomExpressionCRTP<MulExpression>, public INegatable, public IInvertable {
public:
  explicit MulExpression(const ArgumentsPtrVector &children);

  ArgumentPtr negate() const override;

  ArgumentPtr invert() const override;

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
  string childToString(const ArgumentPtr &child, bool isFirst = false) const override;

  static ArgumentPtr simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr multiplicateBraces(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateAndValue(const ArgumentPtr &rhsChild);

  static ArgumentPtr addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value);
};

}