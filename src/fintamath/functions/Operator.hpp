#pragma once

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Operator : public MathObjectImpl<Operator> {
  public:
    explicit Operator(const std::string &str);

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;

  protected:
    bool equals(const Operator &rhs) const override;

  private:
    void parse(const std::string &str);

    char name{};
  };

  namespace types {
    bool isOperator(const std::string &str);
  }
}
