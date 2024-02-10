#pragma once

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class InvTrigExpression final : public IUnaryExpressionCRTP<InvTrigExpression, true> {
public:
  explicit InvTrigExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::InvTrigExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr trigTableSimplify(const IFunction &func, const Rational &rhs);

  static ArgumentPtr trigTableAsinSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAcosSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAtanSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAcotSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAsecSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAcscSimplify(const Rational &rhs);
};

}