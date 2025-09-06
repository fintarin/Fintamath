#include "fintamath/expressions/functions/arithmetic/Add.hpp"

#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Add)

Add::Add(Children inChildren) : Super(std::move(inChildren)) {
}

std::unique_ptr<IFunction> Add::makeFunction(Children inChildren) const {
  return makeObject<Add>(std::move(inChildren));
}

}
