#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperator.hpp"

namespace fintamath {
  class UnaryPlusOperator : public ArithmeticOperator {
  public:
    Set operator()(const Set &set, int64_t precision = 0) const override;

    NodePtr operator()(const Integer &obj) const;
    NodePtr operator()(const Rational &obj) const;

    std::string toString() const override;
  };
}
