#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression> {
public:
  explicit PowExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  std::string toString() const override;

protected:
  // TODO! remove
  ArgumentPtr preSimplify() const override;

  // TODO! remove
  ArgumentPtr postSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  ArgumentPtr polynomSimplify() const;

  ArgumentPtr sumSimplify() const;

  ArgumentPtr mulSimplify() const;

  static ArgumentPtr sumPolynomSimplify(const ArgumentPtr &sumExpr, Integer powValue);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> getPartition(Integer bitNumber, const Integer &variableCount);
};
}