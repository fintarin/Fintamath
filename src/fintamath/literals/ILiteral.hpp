#pragma once

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {
  class ILiteral;
  using LiteralPtr = std::unique_ptr<ILiteral>;

  class ILiteral : virtual public IMathObject {
  public:
    ~ILiteral() override = default;

    static LiteralPtr parse(const std::string &str);
  };

  template <typename Derived>
  class ILiteralCRTP : virtual public ILiteral, virtual public IMathObjectCRTP<Derived> {
  public:
    ~ILiteralCRTP() override = default;

  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}