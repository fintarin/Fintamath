#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Comma,
  {
    .name = ",",
    .argClasses = {IMathObject::getClassStatic()},
    .returnClass = IMathObject::getClassStatic(),
    .operatorDeclaration = OperatorDeclaration{
      .priority = OperatorPriority::Comma,
    },
    .isVariadic = true,
  }
)

IFunction::ArgVector Comma::toFunctionArgs() const {
  if (std::optional compressedArgs = compressArgs()) {
    return *compressedArgs;
  }

  return getArgsVariadic();
}

}
