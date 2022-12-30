#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  Expression Acos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *acos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
