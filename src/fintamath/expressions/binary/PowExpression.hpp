#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/polynomial/SumExpression.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>,
                      public IInvertable,
                      public std::enable_shared_from_this<PowExpression> {
public:
  explicit PowExpression(std::shared_ptr<IMathObject> lhsChild, std::shared_ptr<IMathObject> rhsChild);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  std::shared_ptr<IMathObject> polynomSimplify();

  std::shared_ptr<IMathObject> sumSimplify();

  std::shared_ptr<IMathObject> mulSimplify();

  void invert() override;

  std::shared_ptr<IMathObject> getValue();

  std::shared_ptr<IMathObject> getPow();

protected:
  std::shared_ptr<IMathObject> simplifyChildren() override;

private:
  static std::shared_ptr<IMathObject> sumPolynomSimplify(const SumExpression &sumExpr, Integer pow);

  static Integer generateNextNumber(Integer n);

  static Integer generateFirstNum(const Integer &countOfOne);

  static std::vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
};
}