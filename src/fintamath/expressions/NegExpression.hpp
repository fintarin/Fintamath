#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  NegExpression(const IMathObject &rhs) : IUnaryExpression(rhs) {
  }

  explicit NegExpression(const MathObjectPtr &rhs) : IUnaryExpression(rhs) {
  }

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}