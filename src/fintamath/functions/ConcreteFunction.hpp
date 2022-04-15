#pragma once

#include "fintamath/numbers/Rational.hpp"

#include <string>

namespace fintamath {
  class ConcreteFunction : public MathObjectImpl<ConcreteFunction> {
  public:
    explicit ConcreteFunction(const std::string &str);

    Rational solve(const Rational &rhs, int64_t precision) const;

    Rational solve(const Rational &lhs, const Rational &rhs, int64_t precision) const;

    std::string toString() const override;

  protected:
    bool equals(const ConcreteFunction &rhs) const override;

  private:
    void parse(const std::string &str);

    std::string name;
  };

  namespace types {
    bool isFunction(const std::string &str);

    bool isBinaryFunction(const std::string_view &str);
  }
}
