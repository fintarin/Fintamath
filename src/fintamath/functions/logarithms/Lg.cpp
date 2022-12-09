#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Lg::toString() const {
    return "lg";
  }

  std::string Lg::getClassName() const {
    return "Lg";
  }

  Expression Lg::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *lg(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
