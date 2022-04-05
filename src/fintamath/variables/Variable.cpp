#include "fintamath/variables/Variable.hpp"

#include <regex>

namespace fintamath {
  Variable::Variable(const std::string &str) {
    if (!types::isVariable(str)) {
      throw std::invalid_argument("Variable invalid input");
    }
    name = str;
  }

  std::string Variable::toString() const {
    return name;
  }

  bool Variable::equals(const Variable &rhs) const {
    return this->name == rhs.name;
  }

  namespace types {
    bool isVariable(const std::string &str) {
      std::regex reg(R"([a-df-hj-zA-Z])");
      return regex_search(str, reg);
    }
  }
}
