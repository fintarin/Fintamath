#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
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
    .operatorPriority = IFunction::OperatorPriority::Multiplication,
  }
)

std::unique_ptr<Mul> Mul::make(Arguments inArgs) {
  Mul self;
  self.initSelf(std::move(inArgs));
  return makeObject<Mul>(self);
}

std::unique_ptr<Mul> MulOper::make(Arguments inArgs) {
  return Mul::make(std::move(inArgs));
}

}
