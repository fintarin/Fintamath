#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  ArgumentPtr invert() const override;

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  static ArgumentPtr sumPolynomSimplify(const ArgumentPtr &sumExpr, Integer pow);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);

  ArgumentPtr polynomSimplify() const;

  ArgumentPtr sumSimplify() const;

  ArgumentPtr mulSimplify() const;
};
}