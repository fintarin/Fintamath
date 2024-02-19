#pragma once

#include <string>

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {
class MulExpression final : public IPolynomExpressionCRTP<MulExpression> {
public:
  explicit MulExpression(ArgumentPtrVector inChildren);

  std::string toString() const override;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::MulExpression, "MulExpression"};
  }

protected:
  std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  bool isConstantGreaterThanVariable() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr rationalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr divSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr polynomSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr powSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr trigDoubleAngleSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}