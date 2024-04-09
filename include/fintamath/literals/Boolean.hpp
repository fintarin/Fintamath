#pragma once

#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean : public ILiteralCRTP<Boolean> {
  FINTAMATH_CLASS_BODY(Boolean, ILiteral)

public:
  Boolean();

  template <std::same_as<bool> Bool>
  Boolean(const Bool rhs) : val(rhs) {}

  explicit Boolean(std::string_view str);

  std::string toString() const override;

  explicit operator bool() const;

private:
  bool val;

  static constexpr std::string_view trueStr = "True";

  static constexpr std::string_view falseStr = "False";
};

}
