#include "fintamath/literals/Boolean.hpp"

#include <string_view>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

constexpr std::string_view trueStr = "True";
constexpr std::string_view falseStr = "False";

Boolean::Boolean() : val(falseStr) {
}

Boolean::Boolean(const std::string_view inVal) {
  if (inVal == trueStr) {
    val = trueStr;
  }
  else if (inVal == falseStr) {
    val = falseStr;
  }
  else {
    throw InvalidInputException(fmt::format(R"(Unable to parse a {} from "{}" (expected "True" or "False"))", getTypeStatic().getName(), inVal));
  }
}

Boolean::Boolean(const bool inVal) : val(inVal ? trueStr : falseStr) {
}

std::string Boolean::toString() const {
  return std::string(val);
}

Boolean::operator bool() const {
  return val == trueStr;
}

}
