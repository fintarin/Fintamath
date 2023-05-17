#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class SumExpression : public IPolynomExpressionCRTP<SumExpression> {
public:
  explicit SumExpression(const ArgumentsPtrVector &inChildren);

  // TODO!!! reimplement
  // ArgumentPtr negate() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::SumExpression;
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

  std::string operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  /**
   * @brief
   *
   * @param lhs
   * @param rhs
   * @return -1 if we should swap the arguments
   * @return  1 if we should not swap the arguments
   * @return  0 if this comparator fails
   */
  int comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const override;

private:
  static ArgumentPtr simplifyNumbers(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNegations(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr sumDivisions(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyLogarithms(const IFunction &func, const ArgumentPtr &lhsChild,
                                        const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyMulLogarithms(const IFunction &func, const ArgumentPtr &lhsChild,
                                           const ArgumentPtr &rhsChild);

  static ArgumentPtr sumRates(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &inChild);

  static ArgumentPtr addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value);

  static std::vector<size_t> findLogarithms(const ArgumentsPtrVector &children);

  static std::shared_ptr<const IExpression> mulToLogarithm(const ArgumentsPtrVector &children, size_t i);
};

}