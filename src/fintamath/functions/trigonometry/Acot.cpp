#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Acot::toString() const {
    return "acot";
  }

  Expression Acot::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *acot(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
