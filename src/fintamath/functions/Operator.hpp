#pragma once

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Operator : public Object {
  public:
    explicit Operator(const std::string &strOper);

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;
    std::unique_ptr<Object> clone() const override;
    bool equals(const Object &rhs) const override;

  private:
    char name;
  };

  namespace types {
    bool isOperator(const std::string &str);
  }
}
