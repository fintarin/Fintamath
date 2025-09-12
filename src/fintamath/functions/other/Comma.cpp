#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Comma,
  {
    .name = ",",
    .argumentClasses = {IMathObject::getClassStatic()},
    .returnClass = IMathObject::getClassStatic(),
    .operatorDeclaration = OperatorDeclaration{
      .priority = OperatorPriority::Comma,
    },
    .isVariadic = true,
  }
)

IFunction::Arguments Comma::toFunctionArguments() const {
  if (std::optional compressedArgs = compressArguments()) {
    return *compressedArgs;
  }

  return getArguments();
}

}
