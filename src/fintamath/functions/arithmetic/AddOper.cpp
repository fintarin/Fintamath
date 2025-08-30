#include "fintamath/functions/arithmetic/AddOper.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AddOper)

const AddOper::OperatorDeclaration AddOper::addOperDeclaration = {
  .functionDeclarion = {
    .returnClass = INumber::getClassStatic(),
    .argumentClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    .name = "+",
  },
  .priority = AddOper::Priority::Addition,
};

const AddOper::OperatorDeclaration &AddOper::getOperatorDeclaration() const noexcept {
  return addOperDeclaration;
}

std::unique_ptr<IFunction> AddOper::makeFunctionSelf(Arguments inArgs) const {
  return makeFunction<Add>(std::move(inArgs));
}

}
