#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Tan::toString() const {
    return "tan";
  }

  std::string Tan::getClassName() const {
    return "Tan";
  }

  Expression Tan::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *tan(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
