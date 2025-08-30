#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(
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
    .operatorPriority = OperatorPriority::Comma,
  }
)

Shared<Comma> CommaOper::make(Arguments inArgs) {
  return Comma::make(std::move(inArgs));
}

}
