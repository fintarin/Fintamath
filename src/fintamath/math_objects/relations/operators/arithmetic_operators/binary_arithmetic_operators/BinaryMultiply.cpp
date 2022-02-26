#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMultiply.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T1, typename T2> static std::unique_ptr<Node> multiply(const T1 &lhs, const T2 &rhs);

  std::unique_ptr<Node> BinaryMultiply::operator()(const Set &set) const {
    if (set.size() == 2) {
      INJECT_BINARY_RELATION(Integer, Integer, set)
      INJECT_BINARY_RELATION(Rational, Rational, set)
      INJECT_BINARY_RELATION(Integer, Rational, set)
      INJECT_BINARY_RELATION(Rational, Integer, set)
    }
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> BinaryMultiply::operator()(const Integer &lhs, const Integer &rhs) const {
    return multiply(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMultiply::operator()(const Rational &lhs, const Rational &rhs) const {
    return multiply(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMultiply::operator()(const Integer &lhs, const Rational &rhs) const {
    return multiply(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMultiply::operator()(const Rational &lhs, const Integer &rhs) const {
    return multiply(lhs, rhs);
  }

  std::string BinaryMultiply::toString() const {
    return "*";
  }

  int BinaryMultiply::getPriority() const {
    return 2;
  }
  bool BinaryMultiply::isAssociative() const {
    return true;
  }

  template <typename T1, typename T2> static std::unique_ptr<Node> multiply(const T1 &lhs, const T2 &rhs) {
    return (lhs * rhs).minimize();
  }
}