#include "fintamath/literals/Boolean.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

constexpr std::string_view trueStr = "True";
constexpr std::string_view falseStr = "False";

Boolean::Boolean() : name(falseStr) {
}

Boolean::Boolean(const std::string &str) {
  if (str != trueStr && str != falseStr) {
    throw InvalidInputException(str);
  }

  name = str;
}

Boolean::Boolean(const bool val) : name(val ? trueStr : falseStr) {
}

std::string Boolean::toString() const {
  return name;
}

Boolean::operator bool() const {
  return name == trueStr;
}

}
