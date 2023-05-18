#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class TrigonometryExpression : public IUnaryExpressionCRTP<TrigonometryExpression, true> {
public:
  explicit TrigonometryExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::TrigonometryExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr constantsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}