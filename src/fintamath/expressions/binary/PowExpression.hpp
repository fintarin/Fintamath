#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  MathObjectPtr simplify(bool isPrecise) const override;

  IMathObject *polynomSimplify();

  IMathObject *sumSimplify();

  IMathObject *mulSimplify();

  void invert() override;

  MathObjectPtr getValue();

  MathObjectPtr getPow();

protected:
  IMathObject *simplify() override;

private:
  static IMathObject *sumPolynomSimplify(const SumExpression &sumExpr, Integer pow);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
};
}