#pragma once

#include "fintamath/numbers/Rational.hpp"

#include <string>

namespace fintamath {
  class Function : public MathObject {
  public:
    explicit Function(const std::string &strFunc);

    Rational solve(const Rational &rhs, int64_t precision) const;
    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;
    std::unique_ptr<MathObject> clone() const override;
    bool equals(const MathObject &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isFunction(const std::string &str);
    bool isBinaryFunction(const std::string_view &str);
  }
}
