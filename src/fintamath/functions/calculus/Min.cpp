#include "fintamath/functions/calculus/Min.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Min::call(const ArgumentRefVector &argsVect) const {
  std::reference_wrapper<const IComparable> res = cast<IComparable>(argsVect.front().get());

  for (size_t i = 1; i < argsVect.size(); i++) {
    std::reference_wrapper<const IComparable> arg = cast<IComparable>(argsVect[i].get());

    if (is<Complex>(arg)) {
      return {};
    }

    if (res > arg) {
      res = arg;
    }
  }

  return res.get().clone();
}

}
