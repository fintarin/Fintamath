#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Literal;
  using LiteralPtr = std::unique_ptr<Literal>;

  class Literal : virtual public MathObject {
  public:
    ~Literal() override = default;
  };

  template <typename Derived>
  class LiteralImpl : virtual public Literal, virtual public MathObjectImpl<Derived> {
  public:
    ~LiteralImpl() override = default;

  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}