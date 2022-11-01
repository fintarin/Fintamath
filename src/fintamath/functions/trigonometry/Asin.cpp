#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Asin::toString() const {
    return "asin";
  }

  std::string Asin::getClassName() const {
    return "Asin";
  }

  MathObjectPtr Asin::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return asin(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
