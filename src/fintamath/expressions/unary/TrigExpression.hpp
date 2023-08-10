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

  static ArgumentPtr trigTableSinSimplify(const Rational &rhs);

  static ArgumentPtr trigTableCosSimplify(const Rational &rhs);

  static ArgumentPtr trigTableTanSimplify(const Rational &rhs);

  static ArgumentPtr trigTableCotSimplify(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftSin(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftCos(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftTan(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftCot(const Rational &rhs);

  static Rational phaseShiftPeriod(const Rational &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}