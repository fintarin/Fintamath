#include "fintamath/expressions/functions/arithmetic/Add.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Add)

const Add::FunctionDeclaration Add::addDeclaration = {
  .expressionDeclarion = {
    .domainAndRangeVariants = {{
      .returnClass = INumber::getClassStatic(),
      .childClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    }},
    .isVariadic = true,
  },
  .functionName = "add",
};

Add::Add(Children inChildren) : Super(std::move(inChildren)) {
}

const Add::FunctionDeclaration &Add::getFunctionDeclaration() const noexcept {
  return addDeclaration;
}

std::unique_ptr<IFunction> Add::makeFunctionSelf(Children inChildren) const {
  return makeObject<Add>(Add(std::move(inChildren)));
}

}
