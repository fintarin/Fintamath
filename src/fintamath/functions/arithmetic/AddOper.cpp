#include "fintamath/functions/arithmetic/AddOper.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(AddOper)

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

std::unique_ptr<Add> AddOper::make(Arguments inArgs) {
  return Add::make(std::move(inArgs));
}

}
