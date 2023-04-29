#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

static const std::string INDEX = "_";

Variable::Variable(std::string inName) {
  if (inName.size() != 1) {
    throw InvalidInputException(inName);
  }

  char ch = inName.front();
  if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z')) {
    throw InvalidInputException(inName);
  }

  name = std::move(inName);
}

Variable::Variable(std::string inName, const Integer &inIndex) : Variable(std::move(inName)) {
  if (inIndex <= ZERO) {
    throw InvalidInputException(inName + "_" + inIndex.toString());
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const {
  return name + (index != ZERO ? "_" + index.toString() : "");
}

}
