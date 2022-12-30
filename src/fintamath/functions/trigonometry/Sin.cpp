#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

Expression Sin::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
  return *sin(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
