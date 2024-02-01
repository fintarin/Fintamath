#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

Variable::Variable(std::string inName) {
  if (inName.size() != 1) {
    throw InvalidInputException(inName);
  }

  if (const char ch = inName.front(); ch < 'a' || ch > 'z') {
    throw InvalidInputException(inName);
  }

  name = std::move(inName);
}

Variable::Variable(std::string inName, Integer inIndex) : Variable(std::move(inName)) {
  if (inIndex < 0) {
    throw InvalidInputException(inName + "_" + inIndex.toString());
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const {
  return name + (index != -1 ? "_" + index.toString() : "");
}

}
