#include "fintamath/literals/Boolean.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

const std::string TRUE = "True";
const std::string FALSE = "False";

Boolean::Boolean(const std::string &str) {
  if (str != TRUE && str != FALSE) {
    throw InvalidInputException(str);
  }

  name = str;
}

Boolean::Boolean(bool val) : name(val ? TRUE : FALSE) {
}

std::string Boolean::toString() const {
  return name;
}

Boolean::operator bool() const {
  return name == TRUE;
}

}
