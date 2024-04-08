#include "fintamath/functions/arithmetic/Add.hpp"

#include <memory>
#include <ranges>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Add)

std::unique_ptr<IMathObject> Add::call(const ArgumentRefVector &argVect) const {
  auto res = cast<IArithmetic>(argVect.front().get().clone());

  for (const auto &arg : argVect | std::views::drop(1)) {
    res = *res + cast<IArithmetic>(arg.get());
  }

  return res;
}

}
