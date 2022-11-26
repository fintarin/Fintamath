#include "fintamath/literals/Boolean.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {
  const std::string TRUE = "true";
  const std::string FALSE = "false";

  Boolean::Boolean(const std::string &str) {
    if (str != TRUE && str != FALSE) {
      throw InvalidInputException(*this, str);
    }

    name = str;
  }

  Boolean::Boolean(bool val) : name(val ? TRUE : FALSE) {
  }

  std::string Boolean::toString() const {
    return name;
  }

  std::string Boolean::getClassName() const {
    return "Boolean";
  }

  Boolean::operator bool() const {
    return name == TRUE;
  }
}
