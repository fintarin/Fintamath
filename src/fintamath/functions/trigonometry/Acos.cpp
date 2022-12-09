#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Acos::toString() const {
    return "acos";
  }

  std::string Acos::getClassName() const {
    return "Acos";
  }

  MathObjectPtr Acos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return acos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
