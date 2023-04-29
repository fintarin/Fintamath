#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"
#include "fintamath/expressions/IInvertableExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertableExpression {
public:
  explicit PowExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  ArgumentPtr invert() const override;

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  ArgumentPtr polynomSimplify() const;

  ArgumentPtr sumSimplify() const;

  ArgumentPtr mulSimplify() const;

  // start set of methods for Multinomial theorem
  // https://en.wikipedia.org/wiki/Multinomial_theorem
  // https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
  static ArgumentPtr sumPolynomSimplify(const ArgumentPtr &sumExpr, Integer powValue);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
  // end set of methods for Newton's Polynomial decomposition
};
}