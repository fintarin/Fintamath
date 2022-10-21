#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sin::toString() const {
    return "sin";
  }

  MathObjectPtr Sin::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return sin(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
