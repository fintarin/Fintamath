#include "fintamath/functions/calculus/Integral.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Integral)

using namespace detail;

std::unique_ptr<IMathObject> Integral::call(const ArgumentRefVector &argVect) const {
  return makeExpr(*this, argVect)->toMinimalObject();
}

}
