#include "fintamath/expressions/NegExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

MathObjectPtr NegExpression::simplify() const {
  return {};
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  return {};
}

const IFunction *NegExpression::getFunction() const {
  return &NEG;
}

}
