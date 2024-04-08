#include "fintamath/functions/arithmetic/Frac.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Frac)

std::unique_ptr<IMathObject> Frac::call(const ArgumentRefVector &argVect) const {
  return Div{}(argVect);
}

}
