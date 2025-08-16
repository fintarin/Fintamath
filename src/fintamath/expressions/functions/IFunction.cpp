#include "fintamath/expressions/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::IFunction(Children inChildren) : Super(std::move(inChildren)) {
}

std::string IFunction::toString() const noexcept {
  std::string outStr(getFunctionDeclaration().functionName);
  for (const auto &child : getChildren()) {
    outStr += " " + child->toString();
  }
  return outStr;
}

std::unique_ptr<IFunction> IFunction::makeFunction(Children /*children*/) const {
  return nullptr;
}

}
