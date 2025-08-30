#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(
  Add,
  {
    .name = "add",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorPriority = {},
    .isVariadic = true,
  }
)

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  AddOper,
  {
    .name = "+",
    .argumentClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorPriority = OperatorPriority::Addition,
  }
)

Shared<Add> AddOper::make(Arguments inArgs) {
  return Add::make(std::move(inArgs));
}

}
