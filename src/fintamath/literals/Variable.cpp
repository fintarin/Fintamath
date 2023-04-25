#include "fintamath/literals/Variable.hpp"

#include <regex>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

static const string INDEX = "_";

Variable::Variable(string inName) {
  if (inName.size() != 1) {
    throw InvalidInputException(inName);
  }

  char ch = inName.front();
  if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z')) {
    throw InvalidInputException(inName);
  }

  name = move(inName);
}

Variable::Variable(string inName, Integer inIndex) : Variable(move(inName)) {
  if (inIndex <= ZERO) {
    throw InvalidInputException(inName + "_" + inIndex.toString());
  }

  index = move(inIndex);
}

string Variable::toString() const {
  return name + (index != ZERO ? "_" + index.toString() : "");
}

}
