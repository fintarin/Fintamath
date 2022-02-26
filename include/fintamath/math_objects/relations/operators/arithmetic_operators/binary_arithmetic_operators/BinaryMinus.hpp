#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperator.hpp"

namespace fintamath {
  class BinaryMinus : public BinaryArithmeticOperator {
  public:
    Set operator()(const Set &set) const override;

    std::unique_ptr<Node> operator()(const Integer &lhs, const Integer &rhs) const;
    std::unique_ptr<Node> operator()(const Rational &lhs, const Rational &rhs) const;
    std::unique_ptr<Node> operator()(const Integer &lhs, const Rational &rhs) const;
    std::unique_ptr<Node> operator()(const Rational &lhs, const Integer &rhs) const;

    std::string toString() const override;
    int getPriority() const override;
    bool isAssociative() const override;
  };
}
