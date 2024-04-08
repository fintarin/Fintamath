#include "fintamath/functions/logic/AndOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/logic/And.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AndOper)

std::unique_ptr<IMathObject> AndOper::call(const ArgumentRefVector &argVect) const {
  return And{}(argVect);
}

}
