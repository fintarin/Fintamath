#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Atan::toString() const {
    return "atan";
  }

  Expression Atan::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *atan(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
