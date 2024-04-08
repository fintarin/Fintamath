#include "fintamath/functions/comparison/Eqv.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Eqv)

std::unique_ptr<IMathObject> Eqv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  const auto &rhs = argVect.back().get();

  return Boolean(lhs == rhs).clone();
}

}
