#include "fintamath/functions/logic/Or.hpp"

#include <memory>
#include <ranges>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Or)

std::unique_ptr<IMathObject> Or::call(const ArgumentRefVector &argVect) const {
  auto res = cast<Boolean>(argVect.front().get());

  for (const auto &arg : argVect | std::views::drop(1)) {
    res = res || cast<Boolean>(arg.get());
  }

  return res.clone();
}

}
