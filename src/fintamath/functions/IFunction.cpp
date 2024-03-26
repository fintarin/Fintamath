#include "fintamath/functions/IFunction.hpp"

#include <ranges>
#include <string>
#include <vector>

#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IFunction)

void IFunction::validateArgsSize(const ArgumentRefVector &argVect) const {
  if (!argVect.empty() && (getArgumentClasses().size() == argVect.size() || isVariadic())) {
    return;
  }

  std::vector<std::string> argNameVect(argVect.size());

  for (const auto i : stdv::iota(0U, argNameVect.size())) {
    argNameVect[i] = argVect[i].get().toString();
  }

  throw InvalidInputFunctionException(toString(), argNameVect);
}

}
