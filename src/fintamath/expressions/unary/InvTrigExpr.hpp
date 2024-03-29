#pragma once

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class InvTrigExpr final : public IUnaryExpressionCRTP<InvTrigExpr> {
  FINTAMATH_CLASS_BODY(InvTrigExpr)

public:
  explicit InvTrigExpr(const IFunction &inFunc, ArgumentPtr inChild);

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