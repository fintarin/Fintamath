#pragma once

#include <compare>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class AddExpression final : public IPolynomExpressionCRTP<AddExpression> {
public:
  explicit AddExpression(ArgumentPtrVector inChildren);

  static constexpr MathObjectType getTypeStatic() {
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
  std::strong_ordering compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr logSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulLogSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr trigSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static std::vector<size_t> findLogarithms(const ArgumentPtrVector &children);

  static std::shared_ptr<const IExpression> mulToLogarithm(const ArgumentPtrVector &children, size_t i);
};

}