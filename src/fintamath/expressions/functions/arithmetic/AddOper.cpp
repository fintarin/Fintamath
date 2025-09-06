#include "fintamath/expressions/functions/arithmetic/AddOper.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/functions/arithmetic/Add.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AddOper)

std::unique_ptr<IFunction> AddOper::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

}
