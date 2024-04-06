#pragma once

#include <memory>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class NotExpr : public IUnaryExpressionCRTP<NotExpr> {
  FINTAMATH_CLASS_BODY(NotExpr, IUnaryExpression)

public:
  explicit NotExpr(ArgumentPtr inChild);

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr logicNegatableSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr nestedNotSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getLogicOppositeFunction(const IFunction &function);
};

}