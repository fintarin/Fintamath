#include "fintamath/expressions/functions/arithmetic/AddOper.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/functions/arithmetic/Add.hpp"

namespace fintamath {

std::unique_ptr<Function> AddOper::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

}
