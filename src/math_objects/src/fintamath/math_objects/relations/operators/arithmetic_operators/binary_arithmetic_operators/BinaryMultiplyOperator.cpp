#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMultiplyOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

using namespace fintamath;

template <typename T1, typename T2> static NodePtr multiply(const T1 &lhs, const T2 &rhs);

Set BinaryMultiplyOperator::operator()(const Set &set, int64_t /*precision*/) const {
  INJECT_BINARY_RELATION(Integer, Integer, set)
  INJECT_BINARY_RELATION(Rational, Rational, set)
  INJECT_BINARY_RELATION(Integer, Rational, set)
  INJECT_BINARY_RELATION(Rational, Integer, set)
  throw std::invalid_argument("");
}

NodePtr BinaryMultiplyOperator::operator()(const Integer &lhs, const Integer &rhs) const {
  return multiply(lhs, rhs);
}

NodePtr BinaryMultiplyOperator::operator()(const Rational &lhs, const Rational &rhs) const {
  return multiply(lhs, rhs);
}

NodePtr BinaryMultiplyOperator::operator()(const Integer &lhs, const Rational &rhs) const {
  return multiply(lhs, rhs);
}

NodePtr BinaryMultiplyOperator::operator()(const Rational &lhs, const Integer &rhs) const {
  return multiply(lhs, rhs);
}

std::string BinaryMultiplyOperator::toString() const {
  return "*";
}

template <typename T1, typename T2> static NodePtr multiply(const T1 &lhs, const T2 &rhs) {
  return (lhs * rhs).minimize();
}
