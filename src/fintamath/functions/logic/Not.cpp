#include "fintamath/functions/logic/Not.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Not::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<Boolean>(argVect.front().get());

  return Boolean(!rhs).clone();
}

}
