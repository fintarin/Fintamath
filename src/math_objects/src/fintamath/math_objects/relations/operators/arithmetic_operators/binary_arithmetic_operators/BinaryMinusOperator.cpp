#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

using namespace fintamath;

template <typename T1, typename T2> static NodePtr substract(const T1 &lhs, const T2 &rhs);

Set BinaryMinusOperator::operator()(const Set &set, int64_t /*precision*/) const {
  INJECT_BINARY_RELATION(Integer, Integer, set)
  INJECT_BINARY_RELATION(Rational, Rational, set)
  INJECT_BINARY_RELATION(Integer, Rational, set)
  INJECT_BINARY_RELATION(Rational, Integer, set)
  throw std::invalid_argument("");
}

NodePtr BinaryMinusOperator::operator()(const Integer &lhs, const Integer &rhs) const {
  return substract(lhs, rhs);
}

NodePtr BinaryMinusOperator::operator()(const Rational &lhs, const Rational &rhs) const {
  return substract(lhs, rhs);
}

NodePtr BinaryMinusOperator::operator()(const Integer &lhs, const Rational &rhs) const {
  return substract(lhs, rhs);
}

NodePtr BinaryMinusOperator::operator()(const Rational &lhs, const Integer &rhs) const {
  return substract(lhs, rhs);
}

std::string BinaryMinusOperator::toString() const {
  return "-";
}

template <typename T1, typename T2> static NodePtr substract(const T1 &lhs, const T2 &rhs) {
  auto res = lhs - rhs;
  return std::make_shared<decltype(res)>(res);
}
