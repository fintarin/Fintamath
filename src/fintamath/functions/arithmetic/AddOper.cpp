#include "fintamath/functions/arithmetic/AddOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AddOper)

std::unique_ptr<IMathObject> AddOper::call(const ArgumentRefVector &argVect) const {
  return Add{}(argVect);
}

}
