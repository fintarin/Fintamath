#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivideOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T1, typename T2> static std::unique_ptr<Node> divide(const T1 &lhs, const T2 &rhs);

  Set BinaryDivideOperator::operator()(const Set &set) const {
    INJECT_BINARY_RELATION(Integer, Integer, set)
    INJECT_BINARY_RELATION(Rational, Rational, set)
    INJECT_BINARY_RELATION(Integer, Rational, set)
    INJECT_BINARY_RELATION(Rational, Integer, set)
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> BinaryDivideOperator::operator()(const Integer &lhs, const Integer &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivideOperator::operator()(const Rational &lhs, const Rational &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivideOperator::operator()(const Integer &lhs, const Rational &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivideOperator::operator()(const Rational &lhs, const Integer &rhs) const {
    return divide(lhs, rhs);
  }

  std::string BinaryDivideOperator::toString() const {
    return "/";
  }

  template <typename T1, typename T2> static std::unique_ptr<Node> divide(const T1 &lhs, const T2 &rhs) {
    return (lhs / rhs).minimize();
  }
}