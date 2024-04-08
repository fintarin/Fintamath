#include "fintamath/functions/comparison/Neqv.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Neqv)

std::unique_ptr<IMathObject> Neqv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  const auto &rhs = argVect.back().get();

  return Boolean(lhs != rhs).clone();
}

}
