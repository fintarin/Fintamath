#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryMinusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationUtility.hpp"

using namespace fintamath;

template <typename T> static NodePtr negate(const T &rhs);

Set UnaryMinusOperator::operator()(const Set &set, int64_t /*precision*/) const {
  INJECT_UNARY_RELATION(Integer, set)
  INJECT_UNARY_RELATION(Rational, set)
  throw std::invalid_argument("");
}

NodePtr UnaryMinusOperator::operator()(const Integer &rhs) const {
  return negate(rhs);
}

NodePtr UnaryMinusOperator::operator()(const Rational &rhs) const {
  return negate(rhs);
}

std::string UnaryMinusOperator::toString() const {
  return "-";
}

template <typename T> static NodePtr negate(const T &rhs) {
  return std::make_shared<T>(-rhs);
}
