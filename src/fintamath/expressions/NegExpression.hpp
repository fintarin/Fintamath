#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/UnaryExpression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/multimethod/Converter.hpp"

namespace fintamath {

class NegExpression : public UnaryExpressionCRTP<NegExpression> {
public:
  NegExpression() = default;

  NegExpression(const IMathObject &rhs);

  std::string toString() const override;

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}