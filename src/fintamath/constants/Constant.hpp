#pragma once

#include <memory>

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Constant : public MathObjectImpl<Constant> {
  public:
    explicit Constant(const std::string_view &str);

    Rational toRational(int64_t precision) const;

    std::string toString() const override;

  protected:
    bool equals(const Constant &rhs) const override;

  private:
    std::string name;
  };

  namespace types {
    bool isConstant(const std::string_view &str);
  }
}
