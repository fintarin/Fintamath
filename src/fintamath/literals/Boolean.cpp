#include "fintamath/literals/Boolean.hpp"

#include <string_view>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Boolean)

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

}
