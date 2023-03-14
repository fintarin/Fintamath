#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/interfaces/IInvertable.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(const shared_ptr<IMathObject> &lhsChild, const shared_ptr<IMathObject> &rhsChild);

  // shared_ptr<IMathObject> polynomSimplify();

  // shared_ptr<IMathObject> sumSimplify();

  // shared_ptr<IMathObject> mulSimplify();

  // shared_ptr<IMathObject> getValue();

  // shared_ptr<IMathObject> getPow();

  void invert() override;

protected:
  shared_ptr<IMathObject> postSimplify() const override;

private:
  // static shared_ptr<IMathObject> sumPolynomSimplify(const SumExpression &sumExpr, Integer pow);

  // static Integer generateNextNumber(Integer n);

  // static Integer generateFirstNum(const Integer &countOfOne);

  // static vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
};
}