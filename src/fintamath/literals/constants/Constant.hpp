#pragma once

#include <memory>

#include "fintamath/literals/Literal.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class Constant;
  using ConstantPtr = std::unique_ptr<Constant>;

  class Constant : virtual public Literal {
  public:
    ~Constant() override = default;

    virtual Rational getValue(int64_t precision) const = 0;
  };

  template <typename Derived>
  class ConstantImpl : virtual public Constant, virtual public LiteralImpl<Derived> {
  public:
    ~ConstantImpl() override = default;
  };
}
