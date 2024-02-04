#include "fintamath/functions/calculus/Integral.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Integral::call(const ArgumentRefVector &argVect) const {
  return makeExpr(*this, argVect)->toMinimalObject();
}

}
