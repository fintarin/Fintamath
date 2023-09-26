#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class AddExpression : public IPolynomExpressionCRTP<AddExpression> {
public:
  explicit AddExpression(ArgumentPtrVector inChildren);

  static MathObjectType getTypeStatic() {
    return MathObjectType::AddExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

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
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr sumSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr logSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr mulLogSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr trigSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static std::pair<ArgumentPtr, ArgumentPtr> getRateValuePair(const ArgumentPtr &inChild);

  static ArgumentPtr addRatesToValue(const ArgumentPtrVector &rates, const ArgumentPtr &value);

  static std::vector<size_t> findLogarithms(const ArgumentPtrVector &children);

  static std::shared_ptr<const IExpression> mulToLogarithm(const ArgumentPtrVector &children, size_t i);
};

}