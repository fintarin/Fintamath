#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  MathObjectPtr simplify(bool isPrecise) const override;

  MathObjectPtr polynomialSimplify();

  void invert() override;

protected:
  IMathObject *simplify() override;

private:
  static IMathObject *sumPolynomSimplify(const SumExpression &sumExpr, const Integer &pow);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
};
}