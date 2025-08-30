#pragma once

#include <string>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"

namespace fintamath {

class Boolean : public MathObject {
  FINTAMATH_CLASS_BODY(Boolean, MathObject)

public:
  Boolean();

  template <std::same_as<bool> Bool>
  Boolean(const Bool rhs) noexcept : val(rhs) {}

  explicit Boolean(std::string_view str);

  std::string toString() const noexcept override;

  operator bool() const noexcept;

private:
  bool val;

  static constexpr std::string_view trueStr = "True";

  static constexpr std::string_view falseStr = "False";
};

}
