#include "fintamath/functions/arithmetic/AddF.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  AddF,
  {
    .name = "add",
    .argClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .isVariadic = true,
  }
)

SharedPtr<IMathObject> AddF::preSimplifySelf() const {
  return makeShared<Add>(getArgs());
}

}
