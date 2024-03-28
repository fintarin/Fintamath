#pragma once

#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean final : public ILiteralCRTP<Boolean> {
  FINTAMATH_CLASS_BODY(Boolean)

public:
  Boolean();

  explicit Boolean(const std::string &str);

  template <std::same_as<bool> Bool>
  Boolean(const Bool val) : name(val ? trueStr : falseStr) {
  }

  std::string toString() const override;

  explicit operator bool() const;

private:
  std::string name;

  static constexpr std::string_view trueStr = "True";

  static constexpr std::string_view falseStr = "False";
};

}
