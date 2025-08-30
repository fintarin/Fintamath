#include "fintamath/expressions/functions/Function.hpp"

namespace fintamath {

Function::Function(Children inChildren) : Super(std::move(inChildren)) {
}

std::string Function::toString() const noexcept {
  std::string outStr(getFunctionDeclaration().functionName);
  for (const auto &child : getChildren()) {
    outStr += " " + child->toString();
  }
  return outStr;
}

std::unique_ptr<Function> Function::makeFunction(Children /*children*/) const {
  return nullptr;
}

}
