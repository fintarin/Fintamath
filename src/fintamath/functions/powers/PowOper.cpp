#include "fintamath/functions/powers/PowOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/powers/Pow.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(PowOper)

std::unique_ptr<IMathObject> PowOper::call(const ArgumentRefVector &argVect) const {
  return Pow{}(argVect);
}

}
