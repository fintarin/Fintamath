#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Tan::toString() const {
    return "tan";
  }

  MathObjectPtr Tan::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return tan(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
