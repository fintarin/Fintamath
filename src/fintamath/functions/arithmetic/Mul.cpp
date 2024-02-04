#include "fintamath/functions/arithmetic/Mul.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mul::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IArithmetic>(argVect.front().get());
  const auto &rhs = cast<IArithmetic>(argVect.back().get());

  return lhs * rhs;
}

}
