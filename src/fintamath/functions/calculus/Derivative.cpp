#include "fintamath/functions/calculus/Derivative.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Derivative)

using namespace detail;

std::unique_ptr<IMathObject> Derivative::call(const ArgumentRefVector &argVect) const {
  return makeExpr(*this, argVect)->toMinimalObject();
}

}
