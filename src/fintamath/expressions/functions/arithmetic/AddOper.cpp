#include "fintamath/expressions/functions/arithmetic/AddOper.hpp"

#include "fintamath/core/Arithmetic.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/functions/arithmetic/Add.hpp"

namespace fintamath {

const AddOper::FunctionDeclaration &AddOper::getDeclaration() const noexcept {
  static const MathObjectClass arithmeticClass = Arithmetic::getClassStatic();
  static const FunctionDeclaration declaration = [] {
    FunctionDeclaration outDeclaration;
    outDeclaration.returnClass = arithmeticClass;
    outDeclaration.childClasses = {arithmeticClass, arithmeticClass};
    outDeclaration.isVariadic = false;
    outDeclaration.functionName = "+";
    return outDeclaration;
  }();
  return declaration;
}

std::unique_ptr<Function> AddOper::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

}
