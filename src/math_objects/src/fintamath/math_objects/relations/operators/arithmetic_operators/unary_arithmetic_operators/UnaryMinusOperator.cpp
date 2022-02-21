#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryMinusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T> static std::unique_ptr<Node> negate(const T &rhs);

  Set UnaryMinusOperator::operator()(const Set &set) const {
    INJECT_UNARY_RELATION(Integer, set)
    INJECT_UNARY_RELATION(Rational, set)
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> UnaryMinusOperator::operator()(const Integer &rhs) const {
    return negate(rhs);
  }

  std::unique_ptr<Node> UnaryMinusOperator::operator()(const Rational &rhs) const {
    return negate(rhs);
  }

  std::string UnaryMinusOperator::toString() const {
    return "-";
  }

  template <typename T> static std::unique_ptr<Node> negate(const T &rhs) {
    return std::make_unique<T>(-rhs);
  }
}