#include "fintamath/functions/IFunction.hpp"

#include <ranges>
#include <string>
#include <vector>

#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

void IFunction::validateArgsSize(const ArgumentRefVector &argVect) const {
  if (!argVect.empty() && (getArgumentTypes().size() == argVect.size() || isVariadic())) {
    return;
  }

  std::vector<std::string> argNameVect(argVect.size());

  for (const auto i : stdv::iota(0U, argNameVect.size())) {
    argNameVect[i] = argVect[i].get().toString();
  }

  throw InvalidInputFunctionException(toString(), argNameVect);
}

const IFunction::FunctionNameToOrderMap &IFunction::getFunctionNameToOrderMap() {
  return getFunctionNameToOrderMutableMap();
}

IFunction::FunctionNameToOrderMap &IFunction::getFunctionNameToOrderMutableMap() {
  static FunctionNameToOrderMap map;
  return map;
}

IFunction::FunctionParser &IFunction::getParser() {
  static FunctionParser parser;
  return parser;
}

}
