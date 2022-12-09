#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Sin::toString() const {
    return "sin";
  }

  std::string Sin::getClassName() const {
    return "Sin";
  }

  Expression Sin::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *sin(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
