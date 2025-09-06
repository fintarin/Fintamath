#include "fintamath/functions/other/Comma.hpp"

#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Comma,
  {
    .name = "",
    .argumentClasses = {IMathObject::getClassStatic(), IMathObject::getClassStatic()},
    .returnClass = IMathObject::getClassStatic(),
    .operatorPriority = {},
    .isVariadic = true,
  }
)

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  CommaOper,
  {
    .name = ",",
    .argumentClasses = {IMathObject::getClassStatic(), IMathObject::getClassStatic()},
    .returnClass = IMathObject::getClassStatic(),
    .operatorPriority = IFunction::OperatorPriority::Comma,
  }
)

std::unique_ptr<Comma> Comma::make(Arguments inArgs) {
  Comma self;
  self.initSelf(std::move(inArgs));
  return makeObject<Comma>(self);
}

std::unique_ptr<Comma> CommaOper::make(Arguments inArgs) {
  return Comma::make(std::move(inArgs));
}

}
