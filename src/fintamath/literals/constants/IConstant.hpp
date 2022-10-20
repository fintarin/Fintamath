#pragma once

#include <memory>

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  class IConstant;
  using ConstantPtr = std::unique_ptr<IConstant>;

  class IConstant : virtual public ILiteral {
  public:
    ~IConstant() override = default;

    virtual Rational getValue(int64_t precision) const = 0;

    static ConstantPtr parse(const std::string& str);
  };

  template <typename Derived>
  class IConstantCRTP : virtual public IConstant, virtual public ILiteralCRTP<Derived> {
  public:
    ~IConstantCRTP() override = default;
  };
}
