#include "fintamath/variables/Boolean.hpp"

#include <string_view>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Boolean)
FINTAMATH_CLASS_IMPLEMENTATION(True)
FINTAMATH_CLASS_IMPLEMENTATION(False)

Boolean::Boolean() : val(false) {
}

Boolean::Boolean(const std::string_view str) {
  if (str != trueStr && str != falseStr) {
    throw InvalidInputException(fmt::format(
      R"(Unable to parse {} from "{}" (expected "True" or "False"))",
      getClassStatic()->getName(),
      str
    ));
  }

  val = str == trueStr;
}

std::string Boolean::toString() const noexcept {
  return val ? std::string(trueStr) : std::string(falseStr);
}

Boolean::operator bool() const noexcept {
  return val;
}

std::unique_ptr<IMathObject> True::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(true);
}

std::unique_ptr<IMathObject> False::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
