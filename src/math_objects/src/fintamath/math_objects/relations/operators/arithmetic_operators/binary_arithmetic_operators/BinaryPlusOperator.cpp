#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

using namespace fintamath;

template <typename T1, typename T2> static std::unique_ptr<Node> add(const T1 &lhs, const T2 &rhs);

Set BinaryPlusOperator::operator()(const Set &set, int64_t /*precision*/) const {
  INJECT_BINARY_RELATION(Integer, Integer, set)
  INJECT_BINARY_RELATION(Rational, Rational, set)
  INJECT_BINARY_RELATION(Integer, Rational, set)
  INJECT_BINARY_RELATION(Rational, Integer, set)
  throw std::invalid_argument("");
}

std::unique_ptr<Node> BinaryPlusOperator::operator()(const Integer &lhs, const Integer &rhs) const {
  return add(lhs, rhs);
}

std::unique_ptr<Node> BinaryPlusOperator::operator()(const Rational &lhs, const Rational &rhs) const {
  return add(lhs, rhs);
}

std::unique_ptr<Node> BinaryPlusOperator::operator()(const Integer &lhs, const Rational &rhs) const {
  return add(lhs, rhs);
}

std::unique_ptr<Node> BinaryPlusOperator::operator()(const Rational &lhs, const Integer &rhs) const {
  return add(lhs, rhs);
}

std::string BinaryPlusOperator::toString() const {
  return "+";
}

template <typename T1, typename T2> static std::unique_ptr<Node> add(const T1 &lhs, const T2 &rhs) {
  return (lhs + rhs).minimize();
}
