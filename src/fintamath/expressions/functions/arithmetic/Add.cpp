#include "fintamath/expressions/functions/arithmetic/Add.hpp"

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

Add::Add(Children inChildren) : Super(std::move(inChildren)) {
}

std::unique_ptr<Function> Add::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

const Add::FunctionDeclaration &Add::getDeclaration() const noexcept {
  static const MathObjectClass arithmeticClass = Arithmetic::getClassStatic();
  static const FunctionDeclaration declaration = [] {
    FunctionDeclaration outDeclaration;
    outDeclaration.returnClass = arithmeticClass;
    outDeclaration.childClasses = {arithmeticClass, arithmeticClass};
    outDeclaration.isVariadic = true;
    outDeclaration.functionName = "add";
    return outDeclaration;
  }();
  return declaration;
}

}
