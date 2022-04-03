#pragma once

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Operator : public MathObject<Operator> {
  public:
    explicit Operator(const std::string &str);

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;

    std::unique_ptr<MathObjectBase> clone() const override;

    bool equals(const Operator &rhs) const override;

  private:
    char name;
  };

  namespace types {
    bool isOperator(const std::string &str);
  }
}
