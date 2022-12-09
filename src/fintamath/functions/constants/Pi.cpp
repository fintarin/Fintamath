#include "fintamath/functions/constants/Pi.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Pi::toString() const {
    return "pi";
  }

  std::string Pi::getClassName() const {
    return "Pi";
  }

  Expression Pi::call(const std::vector<std::reference_wrapper<const IMathObject>> & /*argsVect*/) const {
    return pi();
  }
}
