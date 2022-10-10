#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Literal;
  using LiteralPtr = std::unique_ptr<Literal>;

  class Literal : virtual public MathObject {
  public:
    ~Literal() override = default;

    static LiteralPtr parse(const std::string &str);
  };

  template <typename Derived>
  class LiteralCRTP : virtual public Literal, virtual public MathObjectCRTP<Derived> {
  public:
    ~LiteralCRTP() override = default;

  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}