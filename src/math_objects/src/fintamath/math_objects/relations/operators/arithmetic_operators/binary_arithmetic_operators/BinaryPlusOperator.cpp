#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationUtility.hpp"

using namespace fintamath;

template <typename T1, typename T2> static NodePtr add(const T1 &lhs, const T2 &rhs);

Set BinaryPlusOperator::operator()(const Set &set, int64_t /*precision*/) const {
  INJECT_BINARY_RELATION(Integer, Integer, set)
  INJECT_BINARY_RELATION(Rational, Rational, set)
  INJECT_BINARY_RELATION(Integer, Rational, set)
  INJECT_BINARY_RELATION(Rational, Integer, set)
  throw std::invalid_argument("");
}

NodePtr BinaryPlusOperator::operator()(const Integer &lhs, const Integer &rhs) const {
  return add(lhs, rhs);
}

NodePtr BinaryPlusOperator::operator()(const Rational &lhs, const Rational &rhs) const {
  return add(lhs, rhs);
}

NodePtr BinaryPlusOperator::operator()(const Integer &lhs, const Rational &rhs) const {
  return add(Rational(lhs), rhs);
}

NodePtr BinaryPlusOperator::operator()(const Rational &lhs, const Integer &rhs) const {
  return add(lhs, Rational(rhs));
}

std::string BinaryPlusOperator::toString() const {
  return "+";
}

template <typename T1, typename T2> static NodePtr add(const T1 &lhs, const T2 &rhs) {
  auto res = lhs + rhs;
  return std::make_shared<decltype(res)>(res);
}
