#include "fintamath/literals/Boolean.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Boolean)

Boolean::Boolean() : name(falseStr) {
}

Boolean::Boolean(const std::string &str) {
  if (str != trueStr && str != falseStr) {
    throw InvalidInputException(str);
  }

  name = str;
}

std::string Boolean::toString() const {
  return name;
}

Boolean::operator bool() const {
  return name == trueStr;
}

}
