#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acot::toString() const {
    return "acot";
  }

  MathObjectPtr Acot::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return acot(help::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isAdded = IFunction::addParser<Acot>();
}
