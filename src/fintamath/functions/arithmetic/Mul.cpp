#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(
  Mul,
  {
    .name = "mul",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorPriority = {},
    .isVariadic = true,
  }
)

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  MulOper,
  {
    .name = "*",
    .argumentClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorPriority = OperatorPriority::Multiplication,
  }
)

Shared<Mul> MulOper::make(Arguments inArgs) {
  return Mul::make(std::move(inArgs));
}

}
