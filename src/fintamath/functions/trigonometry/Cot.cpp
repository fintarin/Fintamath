#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cot::toString() const {
    return "cot";
  }

  MathObjectPtr Cot::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return cot(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool IS_ADDED = IFunction::addParser<Cot>();
}
