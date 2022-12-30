#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  Expression Cos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *cos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
