#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

Variable::Variable(const std::string &str) {
  if (str.size() != 1) {
    throw InvalidInputException(str);
  }

  char ch = str.front();
  if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z')) {
    throw InvalidInputException(str);
  }

  name = str;
}

std::string Variable::toString() const {
  return name;
}

}
