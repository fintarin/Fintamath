#pragma once

#include <memory>

#include "fintamath/literals/Literal.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Constant : public LiteralImpl<Constant> {
  public:
    explicit Constant(const std::string &str);

    Rational toRational(int64_t precision) const;

    std::string toString() const override;

  private:
    void parse(const std::string &str);

    std::string name;
  };
}
