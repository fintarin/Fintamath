#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Asin::toString() const {
    return "asin";
  }

  std::string Asin::getClassName() const {
    return "Asin";
  }

  Expression Asin::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *asin(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
