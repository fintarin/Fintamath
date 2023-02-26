#include "fintamath/expressions/NegExpression.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

MathObjectPtr NegExpression::simplify() const {
  return {};
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  return {};
}

std::string NegExpression::toString() const {
  return {};
}

const IFunction *NegExpression::getFunction() const {
  return &NEG;
}

}
