#pragma once

#include <memory>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class NotExpression final : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::NotExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr logicNegatableSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr nestedNotSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const IFunction &function);
};

}