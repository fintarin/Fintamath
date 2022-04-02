#pragma once

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Operator : public MathObject {
  public:
    explicit Operator(const std::string &strOper);

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;
    std::unique_ptr<MathObject> clone() const override;
    bool equals(const MathObject &rhs) const override;

  private:
    char name;
  };

  namespace types {
    bool isOperator(const std::string &str);
  }
}
