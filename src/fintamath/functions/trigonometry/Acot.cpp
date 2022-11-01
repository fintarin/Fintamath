#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acot::toString() const {
    return "acot";
  }

  std::string Acot::getClassName() const {
    return "Acot";
  }

  MathObjectPtr Acot::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return acot(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
