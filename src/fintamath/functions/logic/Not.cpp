#include "fintamath/functions/logic/Not.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Not)

std::unique_ptr<IMathObject> Not::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<Boolean>(argVect.front().get());

  return Boolean(!rhs).clone();
}

}
