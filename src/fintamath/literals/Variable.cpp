#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {
  bool isVariable(const std::string &str);

  Variable::Variable(const std::string &str) {
    if (!isVariable(str)) {
      throw InvalidInputException("Variable", str);
    }
    name = str;
  }

  std::string Variable::toString() const {
    return name;
  }

  bool isVariable(const std::string &str) {
    if (str.size() != 1) {
      return false;
    }

    const std::regex reg(R"(^[a-df-hj-zA-Z]$)");
    return regex_search(str, reg);
  }
}
