#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Lb::toString() const {
    return "lb";
  }

  std::string Lb::getClassName() const {
    return "Lb";
  }

  Expression Lb::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *lb(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
