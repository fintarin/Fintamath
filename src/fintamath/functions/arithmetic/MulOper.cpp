#include "fintamath/functions/arithmetic/MulOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(MulOper)

std::unique_ptr<IMathObject> MulOper::call(const ArgumentRefVector &argVect) const {
  return Mul{}(argVect);
}

}
