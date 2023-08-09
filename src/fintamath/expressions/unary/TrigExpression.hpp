#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class Rational;

class TrigExpression : public IUnaryExpressionCRTP<TrigExpression, true> {
public:
  explicit TrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::TrigExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr constantsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr trigTableSimplify(const IFunction &func, const Rational &rhs);

  static ArgumentPtr trigTableSinSimplify(Rational rhs);

  static ArgumentPtr trigTableCosSimplify(Rational rhs);

  static ArgumentPtr trigTableTanSimplify(Rational rhs);

  static ArgumentPtr trigTableCotSimplify(Rational rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}