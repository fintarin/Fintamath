#pragma once

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class InvTrigExpression final : public IUnaryExpressionCRTP<InvTrigExpression> {
public:
  explicit InvTrigExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::InvTrigExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr TrigTableSimplify(const IFunction &func, const Rational &rhs);

  static ArgumentPtr TrigTableAsinSimplify(const Rational &rhs);

  static ArgumentPtr TrigTableAcosSimplify(const Rational &rhs);

  static ArgumentPtr TrigTableAtanSimplify(const Rational &rhs);

  static ArgumentPtr TrigTableAcotSimplify(const Rational &rhs);

  static ArgumentPtr TrigTableAsecSimplify(const Rational &rhs);

  static ArgumentPtr TrigTableAcscSimplify(const Rational &rhs);
};

}