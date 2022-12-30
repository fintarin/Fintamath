#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

Expression Sqrt::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
  return *sqrt(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
