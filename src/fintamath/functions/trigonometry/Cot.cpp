#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Cot::toString() const {
    return "cot";
  }

  std::string Cot::getClassName() const {
    return "Cot";
  }

  Expression Cot::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *cot(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
