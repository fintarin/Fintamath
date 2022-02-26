#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlus.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T1, typename T2> static std::unique_ptr<Node> add(const T1 &lhs, const T2 &rhs);

  Set BinaryPlus::operator()(const Set &set) const {
    INJECT_BINARY_RELATION(Integer, Integer, set)
    INJECT_BINARY_RELATION(Rational, Rational, set)
    INJECT_BINARY_RELATION(Integer, Rational, set)
    INJECT_BINARY_RELATION(Rational, Integer, set)
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> BinaryPlus::operator()(const Integer &lhs, const Integer &rhs) const {
    return add(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryPlus::operator()(const Rational &lhs, const Rational &rhs) const {
    return add(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryPlus::operator()(const Integer &lhs, const Rational &rhs) const {
    return add(lhs, rhs);
  }

  std::unique_ptr<Node> BinaryPlus::operator()(const Rational &lhs, const Integer &rhs) const {
    return add(lhs, rhs);
  }

  std::string BinaryPlus::toString() const {
    return "+";
  }

  int BinaryPlus::getPriority() const {
    return 3;
  }

  template <typename T1, typename T2> static std::unique_ptr<Node> add(const T1 &lhs, const T2 &rhs) {
    return (lhs + rhs).minimize();
  }
}