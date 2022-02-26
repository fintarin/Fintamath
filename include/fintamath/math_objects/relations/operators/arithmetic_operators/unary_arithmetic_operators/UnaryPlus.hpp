#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperator.hpp"

namespace fintamath {
  class UnaryPlus : public UnaryArithmeticOperator {
  public:
    std::unique_ptr<Node> operator()(const Set &set) const override;

    std::unique_ptr<Node> operator()(const Integer &rhs) const;
    std::unique_ptr<Node> operator()(const Rational &rhs) const;

    std::string toString() const override;
    int getPriority() const override;
    bool isAssociative() const override;
  };
}
