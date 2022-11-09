#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Lg::toString() const {
    return "lg";
  }

  std::string Lg::getClassName() const {
    return "Lg";
  }

  MathObjectPtr Lg::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return lg(helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
