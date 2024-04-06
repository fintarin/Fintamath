#pragma once

#include <compare>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class AddExpr : public IPolynomExpressionCRTP<AddExpr> {
  FINTAMATH_CLASS_BODY(AddExpr, IPolynomExpression)

public:
  explicit AddExpr(ArgumentPtrVector inChildren);

  const std::shared_ptr<IFunction> &getOutputFunction() const override;

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

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