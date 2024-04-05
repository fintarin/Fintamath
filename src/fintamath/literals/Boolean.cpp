#include "fintamath/literals/Boolean.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

Boolean::Boolean() : name(falseStr) {
}

Boolean::Boolean(const std::string &str) {
  if (str != trueStr && str != falseStr) {
    throw InvalidInputException(str);
  }

  name = str;
}

std::string Boolean::toString() const noexcept {
  return name;
}

Boolean::operator bool() const {
  return name == trueStr;
}

}
