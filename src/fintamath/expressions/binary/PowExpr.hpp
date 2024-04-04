#pragma once

#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class PowExpr final : public IBinaryExpressionCRTP<PowExpr> {
  FINTAMATH_CLASS_BODY(PowExpr)

public:
  explicit PowExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getOutputFunction() const override;

protected:
  ArgumentPtr approximate() const override;

  ArgumentPtr setPrecision(unsigned precision, const Integer &maxInt) const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr sumPolynomSimplify(const ArgumentPtr &expr, const Integer &power);

  static Integer generateNextNumber(const Integer &n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> getPartition(Integer bitNumber, const Integer &variableCount);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr polynomSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr sumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}