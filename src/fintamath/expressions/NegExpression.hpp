#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/UnaryExpression.hpp"

namespace fintamath {

class NegExpression : public UnaryExpressionCRTP<NegExpression> {
public:
  NegExpression(const IMathObject &rhs) : UnaryExpressionCRTP(rhs) {
  }

  explicit NegExpression(const MathObjectPtr &rhs) : UnaryExpressionCRTP(rhs) {
  }

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}