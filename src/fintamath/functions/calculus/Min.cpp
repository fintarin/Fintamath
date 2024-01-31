#include "fintamath/functions/calculus/Min.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Min::call(const ArgumentRefVector &argVect) const {
  std::reference_wrapper res = cast<IComparable>(argVect.front().get());

  for (const auto &arg : argVect | stdv::drop(1)) {
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
