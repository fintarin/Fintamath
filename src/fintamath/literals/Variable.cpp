#include "fintamath/literals/Variable.hpp"

#include <string>
#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"

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
    throw InvalidInputException(name + "_" + inIndex.toString());
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const {
  return name + (index != -1 ? "_" + index.toString() : "");
}

}
