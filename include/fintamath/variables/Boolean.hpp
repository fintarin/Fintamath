#pragma once

#include <string>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class Boolean : public IMathObject {
  FINTAMATH_CLASS_BODY(Boolean, IMathObject)

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

class True : public IConstant {
  FINTAMATH_CLASS_BODY(True, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

class False : public IConstant {
  FINTAMATH_CLASS_BODY(False, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
