#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

Expression Ln::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
  return *ln(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
