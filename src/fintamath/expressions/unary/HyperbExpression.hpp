#pragma once

#include <memory>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class HyperbExpression final : public IUnaryExpressionCRTP<HyperbExpression, true> {
public:
  explicit HyperbExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::HyperbExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr expandSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}