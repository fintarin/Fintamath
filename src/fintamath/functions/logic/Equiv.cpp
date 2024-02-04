#include "fintamath/functions/logic/Equiv.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Equiv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Boolean>(argVect.front().get());
  const auto &rhs = cast<Boolean>(argVect.back().get());

  return Boolean(lhs == rhs).clone();
}

}
