#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinus.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T1, typename T2> static std::unique_ptr<Node> substract(const T1 &lhs, const T2 &rhs);

  std::unique_ptr<Node> BinaryMinus::operator()(const Set &set) const {
    if (set.size() == 2) {
      INJECT_BINARY_RELATION(Integer, Integer, set)
      INJECT_BINARY_RELATION(Rational, Rational, set)
      INJECT_BINARY_RELATION(Integer, Rational, set)
      INJECT_BINARY_RELATION(Rational, Integer, set)
    }
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> BinaryMinus::operator()(const Integer &lhs, const Integer &rhs) const {
    return substract(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMinus::operator()(const Rational &lhs, const Rational &rhs) const {
    return substract(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMinus::operator()(const Integer &lhs, const Rational &rhs) const {
    return substract(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryMinus::operator()(const Rational &lhs, const Integer &rhs) const {
    return substract(lhs, rhs);
  }

  std::string BinaryMinus::toString() const {
    return "-";
  }

  int BinaryMinus::getPriority() const {
    return 3;
  }

  template <typename T1, typename T2> static std::unique_ptr<Node> substract(const T1 &lhs, const T2 &rhs) {
    return (lhs - rhs).minimize();
  }
}