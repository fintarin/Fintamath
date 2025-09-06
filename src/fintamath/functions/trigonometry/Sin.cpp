#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(
  Sin,
  {
    .name = "sin",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
  }
)

Shared<IMathObject> Sin::approximateSelf() const {
  const auto real = convert<Real>(getArguments().front());
  if (!real) {
    return nullptr;
  }

  return makeShared<Real>(sin(*real));
}

}
