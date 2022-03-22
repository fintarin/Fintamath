#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivide.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T1, typename T2> static std::unique_ptr<Node> divide(const T1 &lhs, const T2 &rhs);

  std::unique_ptr<Node> BinaryDivide::operator()(const Set &set) const {
    if (set.size() == 2) {
      INJECT_BINARY_RELATION(Integer, Integer, set)
      INJECT_BINARY_RELATION(Rational, Rational, set)
      INJECT_BINARY_RELATION(Integer, Rational, set)
      INJECT_BINARY_RELATION(Rational, Integer, set)
    }
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> BinaryDivide::operator()(const Integer &lhs, const Integer &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivide::operator()(const Rational &lhs, const Rational &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivide::operator()(const Integer &lhs, const Rational &rhs) const {
    return divide(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryDivide::operator()(const Rational &lhs, const Integer &rhs) const {
    return divide(lhs, rhs);
  }

  std::string BinaryDivide::toString() const {
    return "/";
  }

  int BinaryDivide::getPriority() const {
    return 2;
  }

  template <typename T1, typename T2> static std::unique_ptr<Node> divide(const T1 &lhs, const T2 &rhs) {
    return (lhs / rhs).minimize();
  }
}