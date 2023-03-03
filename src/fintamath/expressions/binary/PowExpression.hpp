#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  void invert() override;

protected:
  IMathObject *simplify() override;
};
}