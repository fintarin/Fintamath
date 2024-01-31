#include "fintamath/functions/calculus/Max.hpp"

#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Max::call(const ArgumentRefVector &argVect) const {
  std::reference_wrapper<const IComparable> res = cast<IComparable>(argVect.front().get());

  for (auto i : std::views::iota(1U, argVect.size())) {
    std::reference_wrapper<const IComparable> arg = cast<IComparable>(argVect[i].get());

    if (is<Complex>(arg)) {
      return {};
    }

    if (res < arg) {
      res = arg;
    }
  }

  return res.get().clone();
}

}
