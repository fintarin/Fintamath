#include "fintamath/functions/arithmetic/Mul.hpp"

#include <memory>
#include <ranges>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mul::call(const ArgumentRefVector &argVect) const {
  auto res = cast<IArithmetic>(argVect.front().get().clone());

  for (const auto &arg : argVect | std::views::drop(1)) {
    res = *res * cast<IArithmetic>(arg.get());
  }

  return res;
}

}
