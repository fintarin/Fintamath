#pragma once

#include <memory>
#include <tuple>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class TrigExpression final : public IUnaryExpressionCRTP<TrigExpression, true> {
public:
  explicit TrigExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::TrigExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr expandSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr trigTableSimplify(const IFunction &func, const Rational &rhs);

  static ArgumentPtr trigTableSinSimplify(const Rational &rhs);

  static ArgumentPtr trigTableCosSimplify(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftSin(const Rational &rhs);

  static std::tuple<Rational, bool> phaseShiftCos(const Rational &rhs);

  static Rational phaseShiftPeriod(const Rational &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}