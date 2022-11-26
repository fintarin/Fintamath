#include "fintamath/literals/Boolean.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {
  constexpr char *TRUE = "true";
  constexpr char *FALSE = "false";

  bool isBoolean(const std::string &str);

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

  bool isBoolean(const std::string &str) {
    if (str.size() != 1) {
      return false;
    }

    const std::regex reg(R"(^[a-df-hj-zA-Z]$)");
    return regex_search(str, reg);
  }
}
