#include "fintamath/functions/calculus/Max.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Max::call(const ArgumentsRefVector &argsVect) const {
  std::reference_wrapper<const IComparable> res = cast<IComparable>(argsVect.front());

  for (size_t i = 1; i < argsVect.size(); i++) {
    std::reference_wrapper<const IComparable> arg = cast<IComparable>(argsVect[i]);

    if (res < arg) {
      res = arg;
    }
  }

  return res.get().clone();
}

}
