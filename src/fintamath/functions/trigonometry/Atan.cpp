#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Atan::toString() const {
    return "atan";
  }

  MathObjectPtr Atan::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return atan(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
