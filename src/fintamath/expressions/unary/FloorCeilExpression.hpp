#pragma once

#include <memory>

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class FloorCeilExpression final : public IUnaryExpressionCRTP<FloorCeilExpression> {
public:
  explicit FloorCeilExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::FloorCeilExpression, "FloorCeilExpression"};
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}
