#include "fintamath/functions/constants/E.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string E::toString() const {
    return "e";
  }

  std::string E::getClassName() const {
    return "E";
  }

  Expression E::call(const std::vector<std::reference_wrapper<const IMathObject>> & /*argsVect*/) const {
    return e();
  }
}
