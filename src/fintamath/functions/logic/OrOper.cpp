#include "fintamath/functions/logic/OrOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(OrOper)

std::unique_ptr<IMathObject> OrOper::call(const ArgumentRefVector &argVect) const {
  return Or{}(argVect);
}

}
