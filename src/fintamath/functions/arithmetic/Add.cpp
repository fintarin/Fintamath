#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Add)

const Add::FunctionDeclaration Add::addDeclaration = {
  .returnClass = INumber::getClassStatic(),
  .argumentClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
  .isVariadic = true,
  .name = "add",
};

Add::Add(Arguments inArgs) : Super(std::move(inArgs)) {
}

const Add::FunctionDeclaration &Add::getFunctionDeclaration() const noexcept {
  return addDeclaration;
}

std::unique_ptr<IFunction> Add::makeSelf(Arguments inArg) const {
  return make(std::move(inArg));
}

std::unique_ptr<Add> Add::make(Arguments inArgs) {
  return makeObject<Add>(Add(std::move(inArgs)));
}

}
