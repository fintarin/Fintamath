#include "fintamath/functions/calculus/Min.hpp"

#include <functional>
#include <memory>
#include <ranges>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Min)

std::unique_ptr<IMathObject> Min::call(const ArgumentRefVector &argVect) const {
  std::reference_wrapper res = cast<IComparable>(argVect.front().get());

  for (const auto &arg : argVect | std::views::drop(1)) {
    if (is<Complex>(arg)) {
      return {};
    }

    if (const auto &argComp = cast<IComparable>(arg.get()); res > argComp) {
      res = argComp;
    }
  }

  return res.get().clone();
}

}
