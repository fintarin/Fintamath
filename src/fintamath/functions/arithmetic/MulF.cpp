#include "fintamath/functions/arithmetic/MulF.hpp"

#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  MulF,
  {
    .name = "mul",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .isVariadic = true,
  }
)

SharedPtr<IMathObject> MulF::preSimplifySelf() const {
  return makeShared<Mul>(getArguments());
}

}
