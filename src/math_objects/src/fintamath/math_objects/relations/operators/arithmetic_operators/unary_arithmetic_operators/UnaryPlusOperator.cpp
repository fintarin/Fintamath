#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlusOperator.hpp"

#include <stdexcept>

#include "fintamath/math_objects/relations/RelationInjector.hpp"

namespace fintamath {
  template <typename T> static std::unique_ptr<Node> convert(const T &rhs);

  Set UnaryPlusOperator::operator()(const Set &set, int64_t /*precision*/) const {
    INJECT_UNARY_RELATION(Integer, set)
    INJECT_UNARY_RELATION(Rational, set)
    throw std::invalid_argument("");
  }

  std::unique_ptr<Node> UnaryPlusOperator::operator()(const Integer &rhs) const {
    return convert(rhs);
  }

  std::unique_ptr<Node> UnaryPlusOperator::operator()(const Rational &rhs) const {
    return convert(rhs);
  }

  std::string UnaryPlusOperator::toString() const {
    return "+";
  }

  template <typename T> static std::unique_ptr<Node> convert(const T &rhs) {
    return std::make_unique<T>(+rhs);
  }
}