#include "fintamath/functions/logic/And.hpp"

#include <memory>
#include <ranges>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(And)

std::unique_ptr<IMathObject> And::call(const ArgumentRefVector &argVect) const {
  auto res = cast<Boolean>(argVect.front().get());

  for (const auto &arg : argVect | std::views::drop(1)) {
    res = res && cast<Boolean>(arg.get());
  }

  return res.clone();
}

}
