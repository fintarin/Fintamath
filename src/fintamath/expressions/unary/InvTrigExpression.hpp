#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class Rational;

class InvTrigExpression : public IUnaryExpressionCRTP<InvTrigExpression, true> {
public:
  explicit InvTrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::InvTrigExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr trigTableSimplify(const IFunction &func, const Rational &rhs);

  static ArgumentPtr trigTableAsinSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAcosSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAtanSimplify(const Rational &rhs);

  static ArgumentPtr trigTableAcotSimplify(const Rational &rhs);
};

}