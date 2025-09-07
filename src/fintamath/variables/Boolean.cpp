#include "fintamath/variables/Boolean.hpp"

#include <string_view>

#include <fmt/core.h>

#include "fintamath/core/MathObjectUtils.hpp"
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

bool Boolean::equals(const SharedRef<IMathObject> & /*self*/, const SharedRef<IMathObject> &rhs) const noexcept {
  if (const auto rhsBool = cast<Boolean>(rhs)) {
    return equals(*rhsBool);
  }

  return false;
}

bool Boolean::equals(const Boolean &rhs) const noexcept {
  return val == rhs.val;
}

}
