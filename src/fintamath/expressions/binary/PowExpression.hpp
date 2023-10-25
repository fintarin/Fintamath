#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression> {
public:
  explicit PowExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  std::string toString() const override;

  std::shared_ptr<IFunction> getOutputFunction() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::PowExpression;
  }

protected:
  ArgumentPtr approximateSimplify() const override;

  ArgumentPtr setPrecision(uint8_t precision, const Integer &maxInt) const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr sumPolynomSimplify(const ArgumentPtr &sumExpr, const Integer &powValue);

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