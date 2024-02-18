#pragma once

#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class OrExpression final : public IPolynomExpressionCRTP<OrExpression> {
public:
  explicit OrExpression(ArgumentPtrVector inChildren);

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::OrExpression, "OrExpression"};
  }

protected:
  std::string childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const override;

  ArgumentPtr postSimplify() const override;

  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

  bool isComparableOrderInversed() const override;

private:
  static ArgumentPtr boolSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr equalSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr notSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr andSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);

  static ArgumentPtr absorptionSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}