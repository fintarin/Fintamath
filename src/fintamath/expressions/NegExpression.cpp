#include "fintamath/expressions/NegExpression.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const IMathObject &rhs) {
  info = rhs.clone();
}

NegExpression::NegExpression(const NegExpression &rhs) {
  if (this == &rhs) {
    return;
  }
  info = rhs.info->clone();
}

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
