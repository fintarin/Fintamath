#include "fintamath/functions/comparison/LessEqv.hpp"

#include <memory>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> LessEqv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IComparable>(argVect.front().get());
  const auto &rhs = cast<IComparable>(argVect.back().get());

  if (is<Complex>(lhs) || is<Complex>(rhs)) {
    return {};
  }

  return Boolean(lhs <= rhs).clone();
}

}
