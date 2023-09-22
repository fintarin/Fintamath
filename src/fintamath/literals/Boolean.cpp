#include "fintamath/literals/Boolean.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

constexpr char TRUE[] = "True";
constexpr char FALSE[] = "False";

Boolean::Boolean() : name(FALSE) {
}

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
